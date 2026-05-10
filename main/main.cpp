#include <stdio.h>
#include <string.h>

#include "ap_wifi.h"
#include "i2c.h"
#include "key.h"
#include "lcd_rgb.h"
#include "lv_demos.h"
#include "scene_manager.h"

extern "C" void app_main(void)
{
    StatusKey::GetInstance().InitKeys();
    I2CMaster::GetInstance().InitI2C();
    ApWifi::GetInstance().ApWifiInit();
    // SceneManager::GetInstance().SceneManagerInit();
    LcdRgb::GetInstance().LvglPortInit();
    lvgl_port_lock(0);
    lv_demo_music();
    lvgl_port_unlock();
}