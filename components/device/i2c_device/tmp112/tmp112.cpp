#include "tmp112.h"

static const char* TAG = "TMP112";

TMP112::TMP112(i2c_master_bus_handle_t bus, uint16_t addr) : I2CDevice(bus, addr, TAG)
{
}