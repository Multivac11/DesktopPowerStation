#pragma once
#include "i2c_device.h"

class INA226 : public I2CDevice
{
   public:
    INA226(i2c_master_bus_handle_t bus, uint16_t addr);

    bool Configure(uint16_t config_val = 0x4127);

    float ReadBusVoltage();

    float ReadShuntVoltage();

    float ReadCurrent();
};