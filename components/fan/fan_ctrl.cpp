#include "fan_ctrl.h"

static const char* TAG = "FanCtrl";

FanCtrl::FanCtrl(gpio_num_t fan_pin) : fan_pin_(fan_pin)
{
}

void FanCtrl::FanInit()
{
    // 1. 配置 LEDC 定时器：25kHz，10bit 分辨率
    ledc_timer_config_t ledc_timer = {};
    ledc_timer.speed_mode = LEDC_MODE;
    ledc_timer.duty_resolution = PWM_RESOLUTION;
    ledc_timer.timer_num = LEDC_TIMER;
    ledc_timer.freq_hz = PWM_FREQ_HZ;
    ledc_timer.clk_cfg = LEDC_AUTO_CLK;

    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // 2. 配置 LEDC 通道：绑定到 fan_pin_ (GPIO15)
    ledc_channel_config_t ledc_channel = {};
    ledc_channel.gpio_num = fan_pin_;
    ledc_channel.speed_mode = LEDC_MODE;
    ledc_channel.channel = LEDC_CHANNEL;
    ledc_channel.timer_sel = LEDC_TIMER;
    ledc_channel.duty = 0;  // 初始占空比 0（停转）
    ledc_channel.hpoint = 0;
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    ESP_LOGI(TAG, "Fan PWM init OK: GPIO%d, %lu Hz, %d-bit resolution", fan_pin_, PWM_FREQ_HZ, PWM_RESOLUTION);
}

void FanCtrl::SetFanSpeed(uint8_t speed)
{
    if (speed > 100)
    {
        speed = 100;
    }

    // 将 0~100% 映射到 0~1023 duty
    uint32_t duty = (speed * PWM_MAX_DUTY) / 100;

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));

    // ESP_LOGI(TAG, "Fan speed: %3d%% (duty=%4lu/%lu)", speed, duty, PWM_MAX_DUTY);
}
