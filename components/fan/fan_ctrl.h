#pragma once

#include <stdio.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class FanCtrl
{
   public:
    static FanCtrl& GetInstance()
    {
        static FanCtrl instance;
        return instance;
    }

    FanCtrl(gpio_num_t fan_pin = GPIO_NUM_15);

    ~FanCtrl() = default;

    void FanInit();

    void SetFanSpeed(uint8_t speed);

   private:
    gpio_num_t fan_pin_;
};