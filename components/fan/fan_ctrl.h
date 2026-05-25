#pragma once

#include <stdint.h>
#include <stdio.h>

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
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

    void SetFanSpeed(uint8_t speed);  // 输入范围 0 ~ 100 (%)

   private:
    gpio_num_t fan_pin_;

    // LEDC / PWM 配置常量
    static constexpr ledc_mode_t LEDC_MODE = LEDC_LOW_SPEED_MODE;
    static constexpr ledc_timer_t LEDC_TIMER = LEDC_TIMER_0;
    static constexpr ledc_channel_t LEDC_CHANNEL = LEDC_CHANNEL_0;
    static constexpr uint32_t PWM_FREQ_HZ = 25000;  // 标准 4 线风扇 PWM 频率 25kHz
    static constexpr ledc_timer_bit_t PWM_RESOLUTION = LEDC_TIMER_10_BIT;
    static constexpr uint32_t PWM_MAX_DUTY = (1U << PWM_RESOLUTION) - 1;  // 1023
};