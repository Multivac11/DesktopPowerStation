#include "power_monitor.h"

static const char *TAG = "PowerMonitor";

void PowerMonitor::PowerMonitorInit()
{
    bus_data_.ina_ = I2CBusManager::GetInstance().GetDeviceByAddr<INA226>(0x40);
    if (bus_data_.ina_ != nullptr)
    {
        bus_data_.ina_->Configure(0x056F);
        bus_data_.ina_->SetShuntResistor(0.003f, 19.0f);
    }
    else
    {
        ESP_LOGE(TAG, "Bus INA226 not found");
    }
    for (int i = 0; i < 5; i++)
    {
        ina_data_[i].ina_ = I2CBusManager::GetInstance().GetDeviceByAddr<INA226>(0x40 + i);
        if (ina_data_[i].ina_ != nullptr)
        {
            ina_data_[i].ina_->Configure(0x056F);
            ina_data_[i].ina_->SetShuntResistor(0.005f, 7.0f);
        }
        else
        {
            ESP_LOGE(TAG, "INA226 %d not found", i);
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
        if (bus_data_.ina_ != nullptr)
        {
            bus_data_.bus_voltage_ = bus_data_.ina_->ReadBusVoltage();
            bus_data_.current_ = bus_data_.ina_->ReadCurrent();
            bus_data_.power_ = bus_data_.ina_->ReadPower();
        }

        for (int i = 0; i < 5; i++)
        {
            if (ina_data_[i].ina_ != nullptr)
            {
                ina_data_[i].bus_voltage_ = ina_data_[i].ina_->ReadBusVoltage();
                ina_data_[i].current_ = ina_data_[i].ina_->ReadCurrent();
                ina_data_[i].power_ = ina_data_[i].ina_->ReadPower();
            }
        }

        vTaskDelay(pdMS_TO_TICKS(70));
    }
}
