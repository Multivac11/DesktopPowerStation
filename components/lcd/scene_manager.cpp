#include "scene_manager.h"

static const char *TAG = "SceneManager";

void SceneManager::SceneManagerInit()
{
    ESP_LOGI(TAG, "SceneManagerInit");

    LcdRgb::GetInstance().LvglPortInit();

    xTaskCreatePinnedToCore(UIManagerTask, "UIManagerTask", 8096, this, 5, nullptr, 0);
}

void SceneManager::UIManagerTask(void *pvParameters)
{
    static_cast<SceneManager *>(pvParameters)->UIManager();
}

void SceneManager::UIManager()
{
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}