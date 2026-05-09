#include <stdio.h>

#include "ap_wifi.h"
#include "i2c.h"
#include "key.h"

extern "C" void app_main(void)
{
    StatusKey::GetInstance().InitKeys();
    I2CMaster::GetInstance().InitI2C();
    ApWifi::GetInstance().ApWifiInit();
}
