#pragma once

#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2c_bus.h"

#define MAX_LISTENERS 10
#define MAX_INA 5

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
        bool not_found_ = true;
    };

    struct Event
    {
        MonitorData bus_data_;
        MonitorData ina_data_[MAX_INA];
        float temp_ = 0.0f;
    };

    PowerMonitor() = default;

    ~PowerMonitor() = default;

    void PowerMonitorInit();

    static void PowerMonitorTask(void*);

    void Monitor();

    bool RegisterListener(QueueHandle_t queue);

    bool UnregisterListener(QueueHandle_t queue);

   private:
    MonitorData bus_data_;

    MonitorData ina_data_[MAX_INA] = {0};

    TMP112* tmp112_ = nullptr;

    Event event_;

    QueueHandle_t listeners_[MAX_LISTENERS] = {};

    uint8_t listener_count_ = 0;
};
