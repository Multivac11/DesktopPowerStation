#include "scene_manager.h"

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
}

void SceneManager::UIManagerTask(void* pvParameters)
{
    static_cast<SceneManager*>(pvParameters)->UIManager();
}

void SceneManager::UIManager()
{
    LcdDriver& lcd = *lcd_;
    const int W = lcd.Width();   // 960
    const int H = lcd.Height();  // 376

    // ========== 测试 1: 纯色填充 ==========
    ESP_LOGI(TAG, "Test 1: Fill screen colors");
    const uint16_t test_colors[] = {kColorRed, kColorGreen, kColorBlue, kColorWhite, kColorBlack};
    for (auto c : test_colors)
    {
        lcd.FillScreen(c);
        lcd.Flush(panel_);
        vTaskDelay(pdMS_TO_TICKS(400));
    }

    // ========== 测试 2: 矩形 + 文字 ==========
    ESP_LOGI(TAG, "Test 2: Rectangles + text");
    lcd.FillScreen(kColorBlack);
    lcd.FillRect(10, 10, 200, 80, kColorRed);
    lcd.DrawRect(10, 10, 200, 80, kColorWhite);
    lcd.DrawString(30, 40, "Rectangle", kColorWhite, kColorRed);

    lcd.FillRect(230, 10, 200, 80, kColorGreen);
    lcd.DrawRect(230, 10, 200, 80, kColorWhite);
    lcd.DrawString(250, 40, "FillRect", kColorWhite, kColorGreen);

    lcd.FillRect(450, 10, 200, 80, kColorBlue);
    lcd.DrawRect(450, 10, 200, 80, kColorWhite);
    lcd.DrawString(480, 40, "DrawRect", kColorWhite, kColorBlue);

    lcd.FillRect(670, 10, 200, 80, kColorOrange);
    lcd.DrawRect(670, 10, 200, 80, kColorWhite);
    lcd.DrawString(690, 40, "Colors", kColorWhite, kColorOrange);
    lcd.Flush(panel_);
    vTaskDelay(pdMS_TO_TICKS(1500));

    // ========== 测试 3: 线条 ==========
    ESP_LOGI(TAG, "Test 3: Lines");
    lcd.FillScreen(kColorBlack);
    for (int i = 0; i < 10; ++i)
    {
        uint16_t c = RGB565(i * 25, 255 - i * 25, i * 15);
        lcd.DrawLine(0, i * 38, W - 1, (i + 1) * 38, c);
    }
    lcd.DrawLine(0, 0, W - 1, H - 1, kColorWhite);
    lcd.DrawLine(W - 1, 0, 0, H - 1, kColorYellow);
    lcd.DrawString(W / 2 - 40, H / 2 - 8, "Lines", kColorWhite, kColorBlack);
    lcd.Flush(panel_);
    vTaskDelay(pdMS_TO_TICKS(1500));

    // ========== 测试 4: 圆形 ==========
    ESP_LOGI(TAG, "Test 4: Circles");
    lcd.FillScreen(kColorBlack);
    lcd.FillCircle(120, H / 2, 80, kColorBlue);
    lcd.DrawCircle(120, H / 2, 80, kColorWhite);
    lcd.DrawCircle(120, H / 2, 40, kColorYellow);
    lcd.DrawString(60, H / 2 - 8, "Circle1", kColorWhite, kColorBlack);

    lcd.FillCircle(350, H / 2, 60, kColorRed);
    lcd.DrawCircle(350, H / 2, 60, kColorWhite);
    lcd.DrawString(300, H / 2 - 8, "Circle2", kColorWhite, kColorBlack);

    lcd.FillCircle(550, H / 2, 50, kColorGreen);
    lcd.DrawCircle(550, H / 2, 50, kColorWhite);
    lcd.DrawString(500, H / 2 - 8, "Circle3", kColorWhite, kColorBlack);

    lcd.FillCircle(750, H / 2, 90, kColorOrange);
    lcd.DrawCircle(750, H / 2, 90, kColorWhite);
    lcd.DrawCircle(750, H / 2, 45, kColorWhite);
    lcd.DrawString(680, H / 2 - 8, "Circle4", kColorWhite, kColorBlack);
    lcd.Flush(panel_);
    vTaskDelay(pdMS_TO_TICKS(2000));

    // ========== 测试 5: 三种字体对比 ==========
    ESP_LOGI(TAG, "Test 5: Font sizes");
    lcd.FillScreen(kColorBlack);
    lcd.DrawString(10, 10, "32x64 Title", kColorWhite, kColorBlack, kFont32x64);
    lcd.DrawString(10, 80, "16x32 Body", kColorWhite, kColorBlack, kFont16x32);
    lcd.DrawString(10, 120, "8x16 Label Text", kColorWhite, kColorBlack, kFont8x16);
    lcd.DrawString(10, 150, "ABCDEFGHIJK abcdefghijk", kColorCyan, kColorBlack, kFont16x32);
    lcd.DrawString(10, 190, "0123456789 !@#$%", kColorYellow, kColorBlack, kFont16x32);
    lcd.DrawString(10, 230, "Power Station", kColorOrange, kColorBlack, kFont32x64);
    lcd.DrawString(10, 310, "Heiti 8/16/32 x 16/32/64", kColorGray, kColorBlack, kFont8x16);
    lcd.Flush(panel_);
    vTaskDelay(pdMS_TO_TICKS(2500));

    // ========== 测试 6: Dashboard 界面 ==========
    ESP_LOGI(TAG, "Test 6: Dashboard UI");
    lcd.FillScreen(kColorBlack);

    // 顶栏 (16x32)
    lcd.FillRect(0, 0, W, 36, kColorBlue);
    lcd.DrawString(10, 4, "Power Station", kColorWhite, kColorBlue, kFont16x32);
    lcd.DrawString(W - 120, 4, "OK", kColorWhite, kColorBlue, kFont16x32);

    // 左侧: 电池 (标题 16x32, 数据 8x16)
    lcd.DrawRect(5, 42, 310, H - 50, kColorGray);
    lcd.DrawString(15, 48, "Battery", kColorWhite, kColorBlack, kFont16x32);
    lcd.FillRect(20, 88, 200, 20, kColorGreen);
    lcd.DrawRect(20, 88, 200, 20, kColorWhite);
    lcd.DrawString(25, 90, "SOC:85%", kColorBlack, kColorGreen, kFont8x16);
    lcd.DrawString(20, 118, "Volt:25.2V", kColorYellow, kColorBlack, kFont8x16);
    lcd.DrawString(20, 138, "Curr:5.3A", kColorYellow, kColorBlack, kFont8x16);
    lcd.DrawString(20, 158, "Power:133W", kColorYellow, kColorBlack, kFont8x16);
    lcd.DrawString(20, 178, "Temp:32.0C", kColorMagenta, kColorBlack, kFont8x16);
    lcd.DrawString(20, 198, "Cycle:128", kColorGray, kColorBlack, kFont8x16);
    lcd.DrawString(20, 218, "Status:OK", kColorGreen, kColorBlack, kFont8x16);

    // 中间: 太阳能
    lcd.DrawRect(322, 42, 310, H - 50, kColorGray);
    lcd.DrawString(332, 48, "Solar", kColorWhite, kColorBlack, kFont16x32);
    lcd.DrawString(332, 88, "PV:18.5V", kColorOrange, kColorBlack, kFont8x16);
    lcd.DrawString(332, 108, "Cur:2.1A", kColorOrange, kColorBlack, kFont8x16);
    lcd.DrawString(332, 128, "Power:39W", kColorOrange, kColorBlack, kFont8x16);
    lcd.DrawString(332, 148, "MPPT: On", kColorGreen, kColorBlack, kFont8x16);
    lcd.DrawString(332, 168, "Eff: 95%", kColorCyan, kColorBlack, kFont8x16);
    lcd.DrawString(332, 188, "1.2kWh", kColorCyan, kColorBlack, kFont8x16);

    // 右侧: 输出
    lcd.DrawRect(640, 42, 315, H - 50, kColorGray);
    lcd.DrawString(650, 48, "Output", kColorWhite, kColorBlack, kFont16x32);
    lcd.DrawString(650, 88, "USB1:20V", kColorCyan, kColorBlack, kFont8x16);
    lcd.DrawString(650, 108, "USB2:12V", kColorCyan, kColorBlack, kFont8x16);
    lcd.DrawString(650, 128, "DC:12V10A", kColorCyan, kColorBlack, kFont8x16);
    lcd.DrawString(650, 148, "AC:220V", kColorCyan, kColorBlack, kFont8x16);
    lcd.DrawString(650, 168, "Out:133W", kColorWhite, kColorBlack, kFont8x16);
    lcd.DrawString(650, 188, "Fan:1200", kColorGreen, kColorBlack, kFont8x16);

    lcd.DrawString(10, H - 12, "16x32 / 8x16", kColorGreen, kColorBlack, kFont8x16);
    lcd.Flush(panel_);
    vTaskDelay(pdMS_TO_TICKS(3000));

    // ========== 测试 7: 动态动画 (循环) ==========
    ESP_LOGI(TAG, "Test 7: Animation loop");
    while (true)
    {
        int bx = W / 2, by = H / 2, bdx = 5, bdy = 3, br = 25;
        int squares[4][2] = {{100, 100}, {400, 200}, {700, 150}, {550, 300}};
        int sq_dx[4] = {3, -4, 2, -3};
        int sq_dy[4] = {2, 3, -3, -2};

        for (int frame = 0; frame < 400; ++frame)
        {
            lcd.FillScreen(kColorBlack);

            // 标题
            lcd.DrawString(10, 5, "Draw Test", kColorWhite, kColorBlack, kFont16x32);

            // 弹跳球
            lcd.FillCircle(bx, by, br, kColorRed);
            lcd.DrawCircle(bx, by, br, kColorWhite);

            // 移动方块
            for (int s = 0; s < 4; ++s)
            {
                lcd.FillRect(squares[s][0], squares[s][1], 50, 50, kColorGreen + s * 0x0400);
                lcd.DrawRect(squares[s][0], squares[s][1], 50, 50, kColorWhite);
                squares[s][0] += sq_dx[s];
                squares[s][1] += sq_dy[s];
                if (squares[s][0] <= 0 || squares[s][0] >= W - 30) sq_dx[s] = -sq_dx[s];
                if (squares[s][1] <= 20 || squares[s][1] >= H - 30) sq_dy[s] = -sq_dy[s];
            }

            // 扫描线
            int scan = (frame * 10) % H;
            lcd.DrawHLine(0, scan, W, kColorCyan);

            // 角落文字
            lcd.DrawString(W - 80, H - 20, "K270", kColorGray, kColorBlack, kFont8x16);

            lcd.Flush(panel_);

            bx += bdx;
            by += bdy;
            if (bx - br <= 0 || bx + br >= W - 1) bdx = -bdx;
            if (by - br <= 20 || by + br >= H - 1) bdy = -bdy;

            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }
}
