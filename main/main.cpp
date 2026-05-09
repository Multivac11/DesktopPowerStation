#include <stdio.h>

#include "ap_wifi.h"
#include "i2c.h"
#include "key.h"
#include "lcd_rgb.h"

static const char *TAG = "MAIN";

#define COLOR_RED 0xF800
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE 0x001F

extern "C" void app_main(void)
{
    StatusKey::GetInstance().InitKeys();
    I2CMaster::GetInstance().InitI2C();
    ApWifi::GetInstance().ApWifiInit();

    esp_err_t ret = LcdRgb::GetInstance().Init();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "LCD init failed: %s", esp_err_to_name(ret));
        return;
    }

    esp_lcd_panel_handle_t panel = LcdRgb::GetInstance().GetPanel();

    size_t buf_size = LCD_H_RES * LCD_V_RES * sizeof(uint16_t);
    uint16_t *buf = (uint16_t *)heap_caps_malloc(buf_size, MALLOC_CAP_SPIRAM);
    if (buf == nullptr)
    {
        ESP_LOGE(TAG, "PSRAM alloc failed!");
        return;
    }

    while (true)
    {
        for (uint16_t color : {COLOR_RED, COLOR_GREEN, COLOR_BLUE})
        {
            for (int i = 0; i < LCD_H_RES * LCD_V_RES; ++i) buf[i] = color;
            esp_lcd_panel_draw_bitmap(panel, 0, 0, LCD_H_RES, LCD_V_RES, buf);
            ESP_LOGI(TAG, "Draw 0x%04X", color);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}