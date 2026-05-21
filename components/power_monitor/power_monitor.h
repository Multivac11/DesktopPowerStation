#pragma once

class PowerMonitor
{
   public:
    static PowerMonitor& GetInstance()
    {
        static PowerMonitor instance;
        return instance;
    }

    // 统一初始化 I2C 总线并注册所有设备
    void PowerMonitorInit();

   private:
    PowerMonitor() = default;
    ~PowerMonitor() = default;
};
