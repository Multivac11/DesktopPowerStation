#include "scene_manager.h"

static const char *TAG = "SceneManager";

void SceneManager::SceneManagerInit()
{
    ESP_LOGI(TAG, "SceneManagerInit");

    esp_err_t ret = LcdRgb::GetInstance().LcdInit();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "LCD init failed: %s", esp_err_to_name(ret));
        return;
    }

    panel_ = LcdRgb::GetInstance().GetPanel();

    size_t buf_size = LCD_H_RES * LCD_V_RES * sizeof(uint16_t);
    buf_ = (uint16_t *)heap_caps_malloc(buf_size, MALLOC_CAP_SPIRAM);
    if (buf_ == nullptr)
    {
        ESP_LOGE(TAG, "PSRAM alloc failed!");
        return;
    }

    xTaskCreatePinnedToCore(UIManagerTask, "UIManagerTask", 8096, this, 5, nullptr, 0);
}

void SceneManager::UIManagerTask(void *pvParameters)
{
    static_cast<SceneManager *>(pvParameters)->UIManager();
}

void SceneManager::UIManager()
{
    static const uint16_t colors[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE};
    while (true)
    {
        for (uint16_t color : colors)
        {
            for (int i = 0; i < LCD_H_RES * LCD_V_RES; ++i) buf_[i] = color;
            esp_lcd_panel_draw_bitmap(panel_, 0, 0, LCD_H_RES, LCD_V_RES, buf_);
            ESP_LOGI(TAG, "Draw 0x%04X", color);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}