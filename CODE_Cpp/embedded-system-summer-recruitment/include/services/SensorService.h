#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SENSOR_SERVICE_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SENSOR_SERVICE_H

#include "EnvSensorDriver.h"
#include "SoilSensorDriver.h"
#include "OledDisplayDriver.h"

// 传感器聚合服务: 统一 2s 周期采样 + 数据缓存 + OLED 页面刷新
// Driver 层负责读硬件, Service 层负责调度(节流)与汇总。
class SensorService {
    EnvSensorDriver env;          // 温湿度(DHT22)
    SoilSensorDriver soil;        // 土壤湿度(HW-390)
    OledDisplayDriver* display;   // 可选, 传入 nullptr 则不刷新 OLED

    uint32_t lastUpdateMs = 0;
    static constexpr uint32_t UPDATE_INTERVAL_MS = 2000;

public:
    // display 可为 nullptr; soilDry/soilWet 为该板实测标定值, 默认 3290/1057
    SensorService(uint8_t dhtPin, uint8_t soilPin,
                  int soilDry = 3290, int soilWet = 1057,
                  OledDisplayDriver* display = nullptr);

    void begin();

    // 周期采样 + 刷新 OLED(内部节流, 主循环可高频调用)
    void update();

    bool isEnvValid() const;
    float getTemperature() const;
    float getHumidity() const;
    int getSoilPercent() const;   // 0~100, 未采样返回 -1

    String getSensorsJson() const;   // {"temperature":..,"humidity":..,"soil":..}
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_SENSOR_SERVICE_H
