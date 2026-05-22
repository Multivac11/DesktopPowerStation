#include <stdio.h>
#include <string.h>

#include "ap_wifi.h"
#include "device_init.h"
#include "fan_ctrl.h"
#include "key.h"
#include "power_monitor.h"
#include "scene_manager.h"

extern "C" void app_main(void)
{
    StatusKey::GetInstance().InitKeys();
    DeviceInit::GetInstance().Init();
    FanCtrl::GetInstance().FanInit();
    ApWifi::GetInstance().ApWifiInit();
    PowerMonitor::GetInstance().PowerMonitorInit();
    SceneManager::GetInstance().SceneManagerInit();
    // LcdRgb::GetInstance().LvglPortInit();
    // lvgl_port_lock(0);
    // lv_demo_music();
    // lvgl_port_unlock();
}