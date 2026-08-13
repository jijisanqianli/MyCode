#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_ENV_SENSOR_DRIVER_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_ENV_SENSOR_DRIVER_H

#include <Arduino.h>
#include <DHT.h>

// DHT22 温湿度传感器驱动(单总线)
// 注意: DHT22 数据手册要求两次采样间隔 >= 2s,
//       read() 内部做了节流, 直接调用即可, 不会阻塞主循环。
class EnvSensorDriver {
    DHT dht;
    float temperature = NAN;      // 缓存值: °C(上次成功采样的结果)
    float humidity    = NAN;      // 缓存值: %
    uint32_t lastReadMs = 0;      // 节流时间戳
    static constexpr uint32_t SAMPLE_INTERVAL_MS = 2000;

public:
    // dataPin: DATA 引脚; dhtType: DHT11 / DHT22(默认 DHT22)
    explicit EnvSensorDriver(uint8_t dataPin, uint8_t dhtType = DHT22);

    void begin();

    // 节流读取: 距上次采样不足 2s 时直接返回缓存是否有效;
    // 返回 true 表示当前缓存值是有效数据(本次可能未真正采样)。
    bool read();

    float getTemperature() const;
    float getHumidity() const;

    // 最近一次采样是否成功(失败返回 false, 数值为 NAN)
    bool isValid() const;

    String toJson() const;   // {"temperature":27.1,"humidity":64.4} / null
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_ENV_SENSOR_DRIVER_H
