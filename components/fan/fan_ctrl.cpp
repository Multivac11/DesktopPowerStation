#include "fan_ctrl.h"

FanCtrl::FanCtrl(gpio_num_t fan_pin) : fan_pin_(fan_pin)
{
}

void FanCtrl::FanInit()
{
    gpio_config_t gpio_cfg = {
        .pin_bit_mask = (1ULL << fan_pin_),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&gpio_cfg);

    gpio_set_level(fan_pin_, 0);
}
