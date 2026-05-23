#include "scene_manager.h"
#include <cstdio>

static const char* TAG = "SceneManager";

void SceneManager::SceneManagerInit()
{
    esp_err_t ret = LcdRgb::GetInstance().LcdInit();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "LCD init failed: %s", esp_err_to_name(ret));
        return;
    }

    panel_ = LcdRgb::GetInstance().GetPanel();

    size_t buf_size = LCD_H_RES * LCD_V_RES * sizeof(uint16_t);
    buf_ = (uint16_t*)heap_caps_malloc(buf_size, MALLOC_CAP_SPIRAM);
    if (buf_ == nullptr)
    {
        ESP_LOGE(TAG, "PSRAM alloc failed!");
        return;
    }

    lcd_ = new LcdDriver(buf_, LCD_H_RES, LCD_V_RES, Rotation::k270);

    xTaskCreatePinnedToCore(UIManagerTask, "UIManagerTask", 8096, this, 5, nullptr, 0);
    xTaskCreatePinnedToCore(MonitorListenerTask, "MonitorListenerTask", 4096, this, 5, nullptr, 0);
}

void SceneManager::UIManagerTask(void* pvParameters)
{
    static_cast<SceneManager*>(pvParameters)->UIManager();
}

void SceneManager::MonitorListenerTask(void* pvParameters)
{
    static_cast<SceneManager*>(pvParameters)->MonitorListener();
}

// ================== 进度条绘制 ==================
static void DrawBar(LcdDriver& lcd, int x, int y, int w, int h, int r, float pct, uint16_t color)
{
    if (pct < 0.0f) pct = 0.0f;
    if (pct > 1.0f) pct = 1.0f;

    int fill = (int)(w * pct);
    if (fill > 0) lcd.FillRect(x, y, fill, h, color);
    lcd.DrawRoundRect(x, y, w, h, r, color);
}

void SceneManager::UIManager()
{
    LcdDriver& lcd = *lcd_;
    const int W = lcd.Width();
    (void)lcd.Height();

    // ===== CRT 磷光绿色系 =====
    constexpr uint16_t kPhosphor   = 0x07E0;  // 亮绿 (文本/边框)
    constexpr uint16_t kPhosphorDim = 0x0300;  // 暗绿 (标签)
    constexpr uint16_t kCardFill    = 0x0140;  // 卡片底色 深绿
    constexpr uint16_t kBarV        = 0x07E0;  // 电压条 亮绿
    constexpr uint16_t kBarA        = 0x0660;  // 电流条 中绿
    constexpr uint16_t kBarW        = 0x04E0;  // 功率条 暗绿

    constexpr int kCardW = 185;
    constexpr int kCardH = 305;
    constexpr int kCardR = 16;
    constexpr int kCardY = 65;
    constexpr int kCardGap = 6;

    // ===== 静态背景 =====
    lcd.FillScreen(kColorBlack);

    // 顶部装饰线
    lcd.DrawHLine(0, 42, W, kPhosphorDim);
    lcd.DrawHLine(0, 43, W, kPhosphorDim);

    // 卡片 + 扫描线纹理
    for (int i = 0; i < 5; ++i)
    {
        int cx = 6 + i * (kCardW + kCardGap);
        lcd.FillRoundRect(cx, kCardY, kCardW, kCardH, kCardR, kCardFill);
        lcd.DrawRoundRect(cx, kCardY, kCardW, kCardH, kCardR, kPhosphor);

        // CRT 扫描线: 每3行画一条暗线
        for (int y = kCardY + kCardR; y < kCardY + kCardH - kCardR; y += 3)
            lcd.DrawHLine(cx + 8, y, kCardW - 16, kColorBlack);
    }

    // CH1~5 标签
    for (int i = 0; i < 5; ++i)
    {
        int cx = 6 + i * (kCardW + kCardGap);
        char label[4];
        snprintf(label, sizeof(label), "CH%d", i + 1);
        lcd.DrawString(cx + 14, kCardY + 8, label, kPhosphorDim, kCardFill, kFont8x16);
    }

    lcd.Flush(panel_);
    lcd.Flush(panel_);

    float old_bus_v = -1, old_bus_a = -1, old_bus_w = -1;
    float old_v[5] = {-1, -1, -1, -1, -1};
    float old_a[5] = {-1, -1, -1, -1, -1};
    float old_w[5] = {-1, -1, -1, -1, -1};

    while (true)
    {
        if (data_ == nullptr) { vTaskDelay(pdMS_TO_TICKS(70)); continue; }

        auto& ev = *data_;
        char buf[64];
        bool dirty = false;

        // ===== BUS 数据 (左上角) =====
        float bv = ev.bus_data_.bus_voltage_;
        float ba = ev.bus_data_.current_;
        float bw_val = ev.bus_data_.power_;
        if (bv != old_bus_v || ba != old_bus_a || bw_val != old_bus_w)
        {
            snprintf(buf, sizeof(buf), "BUS %.3fV %.3fA %.3fW", bv, ba, bw_val);
            int tw = strlen(buf) * 16;
            lcd.FillRect(0, 0, tw + 20, 40, kColorBlack);
            lcd.DrawString(10, 8, buf, kPhosphor, kColorBlack, kFont16x32);
            old_bus_v = bv; old_bus_a = ba; old_bus_w = bw_val;
            dirty = true;
        }

        // ===== 5 张卡片 =====
        for (int i = 0; i < 5; ++i)
        {
            int cx = 6 + i * (kCardW + kCardGap);
            auto& port = ev.ina_data_[i];
            if (port.ina_ == nullptr) continue;

            int x = cx + 10;
            int vy = kCardY + 26;
            int ay = kCardY + 115;
            int wy = kCardY + 204;

            // 电压
            if (port.bus_voltage_ != old_v[i])
            {
                lcd.FillRect(x, vy, 170, 70, kCardFill);
                // 重画被擦掉的扫描线
                for (int sy = vy; sy < vy + 70; sy += 3)
                    lcd.DrawHLine(x, sy, 160, kColorBlack);
                snprintf(buf, sizeof(buf), "%.3fV", port.bus_voltage_);
                lcd.DrawString(x, vy, buf, kPhosphor, kCardFill, kFont24x48);
                DrawBar(lcd, x, vy + 52, 160, 14, 4, port.bus_voltage_ / 20.0f, kBarV);
                old_v[i] = port.bus_voltage_;
                dirty = true;
            }

            // 电流
            if (port.current_ != old_a[i])
            {
                lcd.FillRect(x, ay, 170, 70, kCardFill);
                for (int sy = ay; sy < ay + 70; sy += 3)
                    lcd.DrawHLine(x, sy, 160, kColorBlack);
                snprintf(buf, sizeof(buf), "%.3fA", port.current_);
                lcd.DrawString(x, ay, buf, kPhosphor, kCardFill, kFont24x48);
                DrawBar(lcd, x, ay + 52, 160, 14, 4, port.current_ / 7.0f, kBarA);
                old_a[i] = port.current_;
                dirty = true;
            }

            // 功率
            if (port.power_ != old_w[i])
            {
                lcd.FillRect(x, wy, 170, 70, kCardFill);
                for (int sy = wy; sy < wy + 70; sy += 3)
                    lcd.DrawHLine(x, sy, 160, kColorBlack);
                snprintf(buf, sizeof(buf), "%.3fW", port.power_);
                lcd.DrawString(x, wy, buf, kPhosphor, kCardFill, kFont24x48);
                DrawBar(lcd, x, wy + 52, 160, 14, 4, port.power_ / 140.0f, kBarW);
                old_w[i] = port.power_;
                dirty = true;
            }
        }

        if (dirty) lcd.Flush(panel_);
        vTaskDelay(pdMS_TO_TICKS(70));
    }
}

void SceneManager::MonitorListener()
{
    QueueHandle_t q = xQueueCreate(1, sizeof(PowerMonitor::Event*));
    PowerMonitor::GetInstance().RegisterListener(q);
    while (true)
    {
        xQueueReceive(q, &data_, portMAX_DELAY);
    }
}
