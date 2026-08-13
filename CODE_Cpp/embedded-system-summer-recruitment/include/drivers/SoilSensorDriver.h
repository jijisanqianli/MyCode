#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SOIL_SENSOR_DRIVER_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SOIL_SENSOR_DRIVER_H

#include <Arduino.h>

// HW-390 电容式土壤湿度传感器驱动(模拟量输出)
// 实测方向: 越湿读数越低(悬空 3290 / 浸水 1057)
// 标定值通过构造函数传入, 换板子/换位置后重新标定即可。
class SoilSensorDriver {
    uint8_t adcPin;
    int dryValue;    // 干燥基准(悬空)
    int wetValue;    // 浸水基准
    int lastRaw = -1;   // 最近一次采样值, -1 表示尚未采样

    static constexpr uint8_t SAMPLE_COUNT = 20;  // 采样次数, 取平均抗 ADC 抖动

public:
    // dryValue/wetValue 默认值为本机实测标定(3290 / 1057)
    explicit SoilSensorDriver(uint8_t adcPin,
                        int dryValue = 3290,
                        int wetValue = 1057);

    void begin();   // 配置 ADC 衰减, 覆盖 0~3.3V 量程

    // 连续采样取平均, 更新 lastRaw 并返回
    int readRaw();

    // 基于标定值映射 0~100%(越湿越高); 未采样时返回 -1
    int getMoisturePercent() const;

    int getLastRaw() const;

    String toJson() const;   // {"soil":35} / {"soil":null}
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SOIL_SENSOR_DRIVER_H
