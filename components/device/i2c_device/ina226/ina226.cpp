#include "ina226.h"

static const char* TAG = "INA226";

INA226::INA226(i2c_master_bus_handle_t bus, uint16_t addr) : I2CDevice(bus, addr, TAG)
{
}

bool INA226::Configure(uint16_t config_val)
{
    uint8_t data[3] = {0x00, (uint8_t)(config_val >> 8), (uint8_t)config_val};
    return Write(data, 3) == ESP_OK;
}

float INA226::ReadBusVoltage()
{
    uint8_t reg = 0x02;
    uint8_t rx[2] = {0};
    if (WriteThenRead(&reg, 1, rx, 2) != ESP_OK) return -1.0f;
    uint16_t raw = (rx[0] << 8) | rx[1];
    return raw * 1.25f / 1000.0f;  // 1.25mV per LSB
}

float INA226::ReadShuntVoltage()
{
    uint8_t reg = 0x01;
    uint8_t rx[2] = {0};
    if (WriteThenRead(&reg, 1, rx, 2) != ESP_OK) return -1.0f;
    int16_t raw = (rx[0] << 8) | rx[1];
    return raw * 2.5f / 1000.0f;  // 2.5uV per LSB -> mV
}

float INA226::ReadCurrent()
{
    uint8_t reg = 0x04;
    uint8_t rx[2] = {0};
    if (WriteThenRead(&reg, 1, rx, 2) != ESP_OK) return -1.0f;
    // 需要根据 Calibration 寄存器计算，这里占位
    return 0.0f;
}