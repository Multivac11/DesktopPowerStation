#include "power_monitor.h"

static const char *TAG = "PowerMonitor";

void PowerMonitor::PowerMonitorInit()
{
    FanCtrl::GetInstance().FanInit();
    FanCtrl::GetInstance().SetFanSpeed(100);
    tmp112_ = I2CBusManager::GetInstance().GetDeviceByAddr<TMP112>(0x48);
    if (tmp112_ != nullptr)
    {
        tmp112_->Init();
    }

    event_.bus_data_.ina_ = I2CBusManager::GetInstance().GetDeviceByAddr<INA226>(0x40);
    if (event_.bus_data_.ina_ != nullptr)
    {
        event_.bus_data_.ina_->Configure(0x056F);
        event_.bus_data_.ina_->SetShuntResistor(0.003f, 19.0f);
        event_.bus_data_.not_found_ = false;
    }
    else
    {
        ESP_LOGE(TAG, "Bus INA226 not found");
        event_.bus_data_.not_found_ = true;
    }
    for (int i = 0; i < 5; i++)
    {
        event_.ina_data_[i].ina_ = I2CBusManager::GetInstance().GetDeviceByAddr<INA226>(0x41 + i);
        if (event_.ina_data_[i].ina_ != nullptr)
        {
            event_.ina_data_[i].ina_->Configure(0x056F);
            event_.ina_data_[i].ina_->SetShuntResistor(0.005f, 7.0f);
            event_.ina_data_[i].not_found_ = false;
        }
        else
        {
            ESP_LOGE(TAG, "INA226 %d not found", i);
            event_.ina_data_[i].not_found_ = true;
        }
    }

    ESP_LOGI(TAG, "PowerMonitorInit");

    xTaskCreatePinnedToCore(PowerMonitorTask, "MonitorTask", 8192, this, 2, nullptr, 1);
    xTaskCreatePinnedToCore(TempControlTask, "TempControlTask", 4096, this, 2, nullptr, 1);
}

void PowerMonitor::PowerMonitorTask(void *pvParameters)
{
    static_cast<PowerMonitor *>(pvParameters)->Monitor();
}

void PowerMonitor::TempControlTask(void *pvParameters)
{
    static_cast<PowerMonitor *>(pvParameters)->TempControl();
}

void PowerMonitor::TempControl()
{
    while (true)
    {
        if (tmp112_ != nullptr)
        {
            event_.temp_ = tmp112_->ReadTemperature();
        }

        float temp = event_.temp_;
        uint8_t speed = event_.fan_speed_;  // 保留当前转速，用于滞回判断

        if (temp >= 60.0f)
        {
            speed = 100;
        }
        else if (temp <= 38.0f)
        {  // 停转阈值比起转阈值低 2°C
            speed = 0;
        }
        else if (temp >= 40.0f && speed == 0)
        {
            // 温度升到 40°C 以上，且当前是停转状态，才启动
            speed = static_cast<uint8_t>((temp - 40.0f) * 5.0f);
        }
        else if (temp > 40.0f && temp < 60.0f && speed > 0)
        {
            // 已经在转，正常跟随曲线
            speed = static_cast<uint8_t>((temp - 40.0f) * 5.0f);
        }
        // 如果 temp 在 38~40°C 且已经在转，保持当前转速，避免抖动

        event_.fan_speed_ = speed;
        FanCtrl::GetInstance().SetFanSpeed(event_.fan_speed_);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void PowerMonitor::Monitor()
{
    while (true)
    {
        if (!event_.bus_data_.not_found_)
        {
            event_.bus_data_.bus_voltage_ = event_.bus_data_.ina_->ReadBusVoltage();
            if (event_.bus_data_.ina_->ReadCurrent() < 0.0f)
            {
                event_.bus_data_.current_ = -event_.bus_data_.ina_->ReadCurrent();
            }
            else
            {
                event_.bus_data_.current_ = event_.bus_data_.ina_->ReadCurrent();
            }
            event_.bus_data_.power_ = event_.bus_data_.ina_->ReadPower();
        }

        for (int i = 0; i < MAX_INA; i++)
        {
            if (!event_.ina_data_[i].not_found_)
            {
                event_.ina_data_[i].bus_voltage_ = event_.ina_data_[i].ina_->ReadBusVoltage();
                if (event_.ina_data_[i].ina_->ReadCurrent() < 0.0f)
                {
                    event_.ina_data_[i].current_ = -event_.ina_data_[i].ina_->ReadCurrent();
                }
                else
                {
                    event_.ina_data_[i].current_ = event_.ina_data_[i].ina_->ReadCurrent();
                }
                event_.ina_data_[i].power_ = event_.ina_data_[i].ina_->ReadPower();
            }
        }

        for (int i = 0; i < listener_count_; ++i)
        {
            if (listeners_[i])
            {
                Event *p = &event_;
                xQueueOverwrite(listeners_[i], &p);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(70));
    }
}

bool PowerMonitor::RegisterListener(QueueHandle_t queue)
{
    if (queue == nullptr || listener_count_ >= MAX_LISTENERS) return false;

    for (int i = 0; i < listener_count_; ++i)
    {
        if (listeners_[i] == queue) return true;  // 已存在，直接返回成功
    }

    listeners_[listener_count_++] = queue;
    return true;
}

bool PowerMonitor::UnregisterListener(QueueHandle_t queue)
{
    for (int i = 0; i < listener_count_; ++i)
    {
        if (listeners_[i] == queue)
        {
            for (int j = i; j < listener_count_ - 1; ++j) listeners_[j] = listeners_[j + 1];
            listeners_[--listener_count_] = nullptr;
            return true;
        }
    }
    return false;
}
