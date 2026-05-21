#pragma once
#include "i2c_device.h"

class TMP112 : public I2CDevice
{
   public:
    TMP112(i2c_master_bus_handle_t bus, uint16_t addr);
};