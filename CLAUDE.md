# CLAUDE.md

本文件为 Claude Code (claude.ai/code) 在此仓库中工作时提供指导。

## 项目概览

DesktopPowerStation 是一个面向便携式储能电源设备的 ESP32-S3 嵌入式固件项目。它驱动一块 376×960 RGB LCD（ST7701S），运行 LVGL 9.5 用户界面，管理 WiFi（AP 配网门户 + STA），处理物理按键输入，并与 I2C 外设通信。

- **目标芯片**：ESP32S3
- **框架**：ESP-IDF v5.5.3
- **构建系统**：ESP-IDF CMake
- **C++ 标准**：C++17

## 构建 / 烧录 / 串口监视

```bash
# 构建
idf.py build

# 通过 UART 烧录
idf.py -p /dev/ttyUSB0 flash

# 构建、烧录并监视
idf.py -p /dev/ttyUSB0 flash monitor

# 完全清理后重新构建
idf.py fullclean build

# VS Code 任务也可通过 Espressif 扩展执行上述命令
```

必须在 ESP-IDF 环境中构建（`. $IDF_PATH/export.sh` 或使用 devcontainer）。

## 架构

### 组件关系图

所有源码模块位于 `components/` 目录下，均遵循单例模式（`GetInstance()`）。`main/main.cpp` 中的初始化顺序为：**按键 → I2C → AP WiFi → LCD/LVGL**。

### `components/lcd/` — 显示
- `lcd_rgb.cpp` — ST7701S 面板驱动。使用 **3 线 9 位 SPI**（SPI2）发送命令，通过 **RGB565 并行接口** 传输像素数据。引脚定义和时序参数均在头文件中。
- `scene_manager.cpp` — 双缓冲 vsync 驱动的帧缓冲管理器。目前在 `app_main` 中被禁用（直接使用 `lv_demo_music()`）。

### `components/wifi_manager/` — 网络
- `wifi_manager.cpp` — WiFi STA 连接管理器，支持 NVS 凭据持久化存储、WiFi 扫描、自动重连（5 轮），以及基于事件的状态广播给已注册的监听者。
- `ap_wifi.cpp` — AP 模式配网门户。通过 HTTP + WebSocket 提供 `/spiffs/apcfg.html` 页面，接收 WiFi 凭据，然后通过 `WifiManager` 连接。通过按键监听在长按时进入 AP 模式。
- `ws_server.cpp` — 轻量级 HTTP + WebSocket 服务器，封装了 ESP-IDF HTTP 服务器。每次提供一个静态 HTML 页面并处理一个 WebSocket 客户端。

### `components/key/` — 按键输入
- 三个 GPIO 按键（引脚 4、5、6），低电平有效，启用内部上拉。以 50 Hz 频率扫描，检测短按、长按（默认 2 秒）和释放。将事件发布到已注册的 FreeRTOS 队列。由 `ApWifi` 用于触发 AP 配网模式。

### `components/i2c_devices/` — I2C 总线
- 初始化 I2C_NUM_0（引脚 SDA:16、SCL:17，100 kHz）。其他外设可共用 `bus_handle_`。

### `main/` — 应用入口
- `app_main` 当前运行 `lv_demo_music()` 作为占位。真正的场景管理器初始化已被注释掉。

### `gui_guider/` — 桌面模拟（非嵌入式）
- 一个独立的 NXP GUI Guider 项目，用于在 Linux 上通过 Wayland 设计 LVGL 界面。其 `CMakeLists.txt` 为主机构建一个独立的 LVGL 可执行文件，**而非** ESP32 目标。不要在其中修改嵌入式 UI 代码——嵌入式 LVGL 代码应放在 `components/lcd/` 或 `main/` 目录下。

## 分区表

定义在 `partitions_webserver.csv` 中：NVS（0x6000）、phy_init（0x1000）、factory 应用（4M）、SPIFFS HTML 存储（128K）。HTML 配网页烧录在 `html` SPIFFS 分区中。

## 代码风格

`.clang-format` 基于 Google 风格衍生：4 空格缩进、120 字符列宽限制、指针左对齐、`AfterClass: true` / `AfterFunction: true` 大括号换行。gui_guider 下的 LVGL C 文件可能使用 2 空格缩进——不要混用风格。

## 关键引脚参考

| GPIO | 功能 |
|------|------|
| 1, 2, 42 | LCD SPI（CS, SCL, SDA） |
| 3, 9-14, 21, 38-41, 45-48 | LCD RGB 数据 |
| 7, 8, 18, 19, 20 | LCD 背光、HSYNC、VSYNC、PCLK、DE |
| 4, 5, 6 | 按键 |
| 16, 17 | I2C（SDA, SCL） |
