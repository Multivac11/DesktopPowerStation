#include "power_monitor.h"

static const char *TAG = "PowerMonitor";

void PowerMonitor::PowerMonitorInit()
{
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
}

void PowerMonitor::PowerMonitorTask(void *pvParameters)
{
    static_cast<PowerMonitor *>(pvParameters)->Monitor();
}

void PowerMonitor::Monitor()
{
    while (true)
    {
        if (tmp112_ != nullptr)
        {
            event_.temp_ = tmp112_->ReadTemperature();
        }
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
