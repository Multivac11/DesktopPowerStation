#pragma once

#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lcd_rgb.h"

#define COLOR_RED 0xF800
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE 0x001F

class SceneManager
{
   public:
    static SceneManager &GetInstance()
    {
        static SceneManager instance;

        return instance;
    }

    SceneManager() = default;

    ~SceneManager() = default;

    void SceneManagerInit();

    static void UIManagerTask(void *);

    void UIManager();

    volatile bool vsync_flag_ = false;

    void *fb_[2] = {nullptr, nullptr};

   private:
    esp_lcd_panel_handle_t panel_ = nullptr;

    uint16_t *buf_ = nullptr;
};
