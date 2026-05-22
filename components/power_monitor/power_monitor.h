#pragma once

#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2c_bus.h"

class PowerMonitor
{
   public:
    static PowerMonitor& GetInstance()
    {
        static PowerMonitor instance;
        return instance;
    }

    struct MonitorData
    {
        INA226* ina_ = nullptr;
        float bus_voltage_ = 0.0f;
        float shunt_voltage_ = 0.0f;
        float current_ = 0.0f;
        float power_ = 0.0f;
    };

    PowerMonitor() = default;

    ~PowerMonitor() = default;

    void PowerMonitorInit();

    static void PowerMonitorTask(void*);

    void Monitor();

   private:
    MonitorData bus_data_;

    MonitorData ina_data_[5] = {0};
};
