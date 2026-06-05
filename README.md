# DesktopPowerStation

> 桌面充电站 — 基于 ESP32-S3 的五路独立智能充电电源，内置 450W 开关电源，每路最高支持 140W 输出。

## 硬件特性

- **电源输入**：交流输入，内置 450W 开关电源
- **五路独立输出**：每路最高支持 **140W**（PD 3.1），总功率不超过 450W
- **实时功率监测**：6 颗 TI INA226 高精度电流/功率监测芯片（1 颗总线 + 5 颗通道），I2C 通信
- **温度监控**：TI TMP112 高精度数字温度传感器，支持温控风扇调速
- **散热风扇**：PWM 调速风扇，根据温度自动调节转速
- **物理按键**：3 个 GPIO 按键，支持短按/长按操作
- **高清屏幕**：376×960 分辨率 ST7701S RGB LCD，16 位色深（RGB565）
- **WiFi 联网**：支持 STA 模式连接路由器，AP 模式配网门户

## 软件特性

- **LVGL 9.5 图形界面**：流畅的 30 FPS 嵌入式 UI，支持多字体中文显示
- **配网门户**：长按按键进入 AP 模式，手机连接后通过网页配置 WiFi 凭据
- **WebSocket 通信**：配网页面通过 WebSocket 与设备交互
- **NVS 持久化**：WiFi 凭据掉电保存，自动重连
- **FreeRTOS 多任务**：UI 渲染、电源监测、温度控制独立任务运行
- **事件驱动架构**：各组件通过 FreeRTOS 队列发布/订阅事件

## 硬件规格

| 类别 | 参数 |
|------|------|
| 主控芯片 | ESP32-S3（Xtensa LX7 双核 @ 240 MHz） |
| 存储 | 16 MB Flash（QIO）、Octal SPI PSRAM |
| 显示屏 | ST7701S 376×960 RGB LCD（SPI 命令 + RGB565 并口数据） |
| 电流监测 | 6× TI INA226（I2C 地址 0x40-0x45） |
| 温度传感器 | 1× TI TMP112（I2C 地址 0x48） |
| 风扇控制 | PWM（25 kHz，10 位精度） |
| 按键 | 3× 轻触按键（GPIO 4/5/6，低电平有效） |

### GPIO 引脚定义

| GPIO | 功能 |
|------|------|
| 1, 2, 42 | LCD SPI（CS, SCL, SDA） |
| 3, 9-14, 21, 38-41, 45-48 | LCD RGB 数据线 |
| 7 | LCD 背光 |
| 8 | HSYNC |
| 18 | VSYNC |
| 19 | PCLK |
| 20 | DE |
| 4, 5, 6 | 物理按键 |
| 15 | 风扇 PWM |
| 16, 17 | I2C（SDA, SCL） |

## 软件架构

```
main/
  main.cpp                     # 应用入口，初始化各组件
components/
  lcd/                         # 显示子系统
    lcd_rgb.cpp                # ST7701S 面板驱动
    lcd_driver.cpp             # 软件 2D 渲染引擎
    scene_manager.cpp          # LVGL 场景管理 & UI 任务
    font/                      # 黑体字库（8×16 / 16×32 / 24×48 / 32×64）
  power_monitor/               # 电源监测
    power_monitor.cpp          # 聚合 INA226 + TMP112 数据，发布事件
  device/                      # 硬件初始化
    device_init.cpp            # 初始化 I2C 总线及外设
    i2c_device/
      i2c_bus.cpp              # I2C 总线管理器
      ina226/                  # INA226 驱动
      tmp112/                  # TMP112 驱动
  wifi_manager/                # 网络
    wifi_manager.cpp           # WiFi STA 管理（连接/扫描/重连）
    ap_wifi.cpp                # AP 配网门户
    ws_server.cpp              # HTTP + WebSocket 服务器
  key/                         # 按键输入
    key.cpp                    # 50 Hz 按键扫描 & 事件分发
  fan/                         # 风扇控制
    fan_ctrl.cpp               # PWM 风扇调速
```

所有组件均采用**单例模式**（`GetInstance()`），通过 FreeRTOS 队列实现松耦合的事件通信。

### 初始化流程

```
按键 → I2C 总线 → 外设（INA226 / TMP112）→ WiFi 配网 → 电源监测 → LVGL 界面
```

## 构建

### 环境要求

- ESP-IDF v5.5.3
- C++17 编译器（xtensa-esp32s3-elf-g++）
- 或使用 VS Code + Dev Container（Espressif 官方镜像）

### 构建步骤

```bash
# 激活 ESP-IDF 环境
. $IDF_PATH/export.sh

# 构建项目
idf.py build

# 烧录到设备（UART）
idf.py -p /dev/ttyUSB0 flash

# 构建 + 烧录 + 串口监视
idf.py -p /dev/ttyUSB0 flash monitor

# 完全清理重新构建
idf.py fullclean build
```

### 分区表

| 分区名 | 类型 | 大小 | 用途 |
|--------|------|------|------|
| nvs | data/nvs | 24 KB | WiFi 凭据等持久化数据 |
| phy_init | data/phy | 4 KB | PHY 初始化参数 |
| factory | app/factory | 4 MB | 固件 |
| html | data/spiffs | 128 KB | 配网网页（apcfg.html） |

## 桌面模拟器

`gui_guider/` 目录包含一个独立的 LVGL 桌面模拟器项目，可在 Linux 上通过 Wayland 运行，用于界面设计和调试。使用独立的 CMake 构建，不依赖 ESP-IDF。

## 许可证

MIT License
