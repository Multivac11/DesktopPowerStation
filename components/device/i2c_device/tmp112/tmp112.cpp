#include "tmp112.h"

static const char* TAG = "TMP112";

TMP112::TMP112(i2c_master_bus_handle_t bus, uint16_t addr) : I2CDevice(bus, addr, TAG)
{
}

bool TMP112::Init()
{
    if (!I2CDevice::Init())
    {
        return false;
    }

    uint16_t cfg = ReadConfig();
    if (cfg == 0)
    {
        ESP_LOGE(TAG, "Failed to read config at 0x%02X", device_address_);
        return false;
    }

    // 验证 R1/R0 固定为 11（12-bit 分辨率标志）
    if ((cfg & (CFG_R1 | CFG_R0)) != (CFG_R1 | CFG_R0))
    {
        ESP_LOGW(TAG, "Unexpected config: 0x%04X", cfg);
    }

    extended_mode_ = (cfg & CFG_EM) != 0;
    ESP_LOGI(TAG, "Init OK, addr=0x%02X, config=0x%04X, %s mode", device_address_, cfg,
             extended_mode_ ? "13-bit" : "12-bit");
    return true;
}

/* ---------- 底层寄存器读写 ---------- */

bool TMP112::WriteReg(uint8_t reg, uint16_t val)
{
    uint8_t data[3] = {reg, static_cast<uint8_t>(val >> 8), static_cast<uint8_t>(val)};
    return Write(data, 3) == ESP_OK;
}

uint16_t TMP112::ReadReg(uint8_t reg)
{
    uint8_t rx[2] = {0};
    if (WriteThenRead(&reg, 1, rx, 2) != ESP_OK)
    {
        ESP_LOGE(TAG, "ReadReg 0x%02X failed at 0x%02X", reg, device_address_);
        return 0;
    }
    return (static_cast<uint16_t>(rx[0]) << 8) | rx[1];
}

/* ---------- 温度读取 ---------- */

float TMP112::ReadTemperature()
{
    return ReadTemperatureRaw() * 0.0625f;
}

int16_t TMP112::ReadTemperatureRaw()
{
    uint16_t raw = ReadReg(REG_TEMP);

    if (extended_mode_)
    {
        // 13-bit 扩展模式：算术右移 3 位，保留符号
        return static_cast<int16_t>(raw) >> 3;
    }
    else
    {
        // 12-bit 标准模式：算术右移 4 位，保留符号
        return static_cast<int16_t>(raw) >> 4;
    }
}

/* ---------- 配置寄存器 ---------- */

bool TMP112::WriteConfig(uint16_t config)
{
    ESP_LOGI(TAG, "WriteConfig: 0x%04X", config);
    if (!WriteReg(REG_CONFIG, config))
    {
        return false;
    }
    extended_mode_ = (config & CFG_EM) != 0;
    return true;
}

uint16_t TMP112::ReadConfig()
{
    return ReadReg(REG_CONFIG);
}

/* ---------- 快捷配置 ---------- */

bool TMP112::SetConversionRate(uint8_t conversion_rate)
{
    if (conversion_rate > 3)
    {
        ESP_LOGE(TAG, "Invalid conversion rate: %u", conversion_rate);
        return false;
    }
    uint16_t cfg = ReadConfig();
    cfg &= ~(CFG_CR1 | CFG_CR0);
    cfg |= (static_cast<uint16_t>(conversion_rate) << 6) & (CFG_CR1 | CFG_CR0);
    return WriteConfig(cfg);
}

bool TMP112::SetExtendedMode(bool enable)
{
    uint16_t cfg = ReadConfig();
    if (enable)
    {
        cfg |= CFG_EM;
    }
    else
    {
        cfg &= ~CFG_EM;
    }
    return WriteConfig(cfg);
}

bool TMP112::SetShutdown(bool shutdown)
{
    uint16_t cfg = ReadConfig();
    if (shutdown)
    {
        cfg |= CFG_SD;
    }
    else
    {
        cfg &= ~CFG_SD;
    }
    return WriteConfig(cfg);
}

bool TMP112::TriggerOneShot()
{
    uint16_t cfg = ReadConfig();
    if ((cfg & CFG_SD) == 0)
    {
        ESP_LOGW(TAG, "Not in shutdown mode, cannot trigger one-shot");
        return false;
    }
    cfg |= CFG_OS;
    return WriteConfig(cfg);
}

/* ---------- 阈值寄存器 ---------- */

static uint16_t TempToReg(float temp, bool extended)
{
    int16_t lsb = static_cast<int16_t>(temp / 0.0625f);
    if (extended)
    {
        return static_cast<uint16_t>(lsb << 3);
    }
    else
    {
        return static_cast<uint16_t>(lsb << 4);
    }
}

static float RegToTemp(uint16_t reg, bool extended)
{
    int16_t lsb;
    if (extended)
    {
        lsb = static_cast<int16_t>(reg) >> 3;
    }
    else
    {
        lsb = static_cast<int16_t>(reg) >> 4;
    }
    return lsb * 0.0625f;
}

bool TMP112::SetTlow(float temp)
{
    return WriteReg(REG_TLOW, TempToReg(temp, extended_mode_));
}

bool TMP112::SetThigh(float temp)
{
    return WriteReg(REG_THIGH, TempToReg(temp, extended_mode_));
}

float TMP112::ReadTlow()
{
    return RegToTemp(ReadReg(REG_TLOW), extended_mode_);
}

float TMP112::ReadThigh()
{
    return RegToTemp(ReadReg(REG_THIGH), extended_mode_);
}
