#pragma once
#include "i2c_device.h"

class TMP112 : public I2CDevice
{
   public:
    explicit TMP112(i2c_master_bus_handle_t bus, uint16_t addr);

    bool Init() override;

    // ---------- 温度读取 ----------
    float ReadTemperature();       // 读取温度 (°C)
    int16_t ReadTemperatureRaw();  // 原始值 (已按位数右移，1 LSB = 0.0625°C)

    // ---------- 配置寄存器 ----------
    bool WriteConfig(uint16_t config);
    uint16_t ReadConfig();

    // ---------- 快捷配置 ----------
    // conversion_rate: 0=0.25Hz, 1=1Hz, 2=4Hz(default), 3=8Hz
    bool SetConversionRate(uint8_t conversion_rate);
    bool SetExtendedMode(bool enable);  // true=13位, false=12位(默认)
    bool SetShutdown(bool shutdown);    // true=关机, false=连续转换
    bool TriggerOneShot();              // 触发单次转换（需先进入关机模式）

    // ---------- 阈值寄存器 (°C) ----------
    bool SetTlow(float temp);
    bool SetThigh(float temp);
    float ReadTlow();
    float ReadThigh();

   private:
    bool WriteReg(uint8_t reg, uint16_t val);
    uint16_t ReadReg(uint8_t reg);

    static constexpr uint8_t REG_TEMP = 0x00;
    static constexpr uint8_t REG_CONFIG = 0x01;
    static constexpr uint8_t REG_TLOW = 0x02;
    static constexpr uint8_t REG_THIGH = 0x03;

    // Configuration register bit masks (16-bit, MSB first)
    static constexpr uint16_t CFG_OS = 0x8000;   // One-Shot / Conversion Ready
    static constexpr uint16_t CFG_R1 = 0x4000;   // Resolution bit 1 (RO, always 1)
    static constexpr uint16_t CFG_R0 = 0x2000;   // Resolution bit 0 (RO, always 1)
    static constexpr uint16_t CFG_F1 = 0x1000;   // Fault Queue bit 1
    static constexpr uint16_t CFG_F0 = 0x0800;   // Fault Queue bit 0
    static constexpr uint16_t CFG_POL = 0x0400;  // ALERT Polarity
    static constexpr uint16_t CFG_TM = 0x0200;   // Thermostat Mode
    static constexpr uint16_t CFG_SD = 0x0100;   // Shutdown
    static constexpr uint16_t CFG_CR1 = 0x0080;  // Conversion Rate bit 1
    static constexpr uint16_t CFG_CR0 = 0x0040;  // Conversion Rate bit 0
    static constexpr uint16_t CFG_EM = 0x0010;   // Extended Mode (13-bit), bit 4

    bool extended_mode_ = false;
};
