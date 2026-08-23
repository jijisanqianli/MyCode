#include "SensorService.h"
#include <freertos/FreeRTOS.h>   // portENTER_CRITICAL / portEXIT_CRITICAL

SensorService::SensorService(uint8_t dhtPin, uint8_t soilPin,
                             int soilDry, int soilWet,
                             OledDisplayDriver* display)
    : env(dhtPin), soil(soilPin, soilDry, soilWet), display(display) {}

void SensorService::begin() {
    env.begin();
    soil.begin();
}

void SensorService::update() {
    // 节流: 每 UPDATE_INTERVAL_MS 采样一轮
    uint32_t now = millis();
    if (now - lastUpdateMs < UPDATE_INTERVAL_MS) return;
    lastUpdateMs = now;

    env.read();      // EnvSensorDriver 内部已按 2s 节流
    soil.readRaw();  // 20 次采样取平均, 约 100ms 阻塞(2s 周期内可接受)

    if (display != nullptr) {
        display->showSensors(env.getTemperature(), env.getHumidity(),
                             soil.getMoisturePercent());
    }
}

bool SensorService::isEnvValid() const {
    return env.isValid();
}

float SensorService::getTemperature() const {
    return env.getTemperature();
}

float SensorService::getHumidity() const {
    return env.getHumidity();
}

int SensorService::getSoilPercent() const {
    return soil.getMoisturePercent();
}

// 打包一次采样快照: 短临界区保证三个字段来自同一次读取(避免混合快照)
SensorData_t SensorService::getData() const {
    // ESP32(双核) 的临界区需要显式 spinlock
    static portMUX_TYPE criticalMux = portMUX_INITIALIZER_UNLOCKED;

    SensorData_t data;
    portENTER_CRITICAL(&criticalMux);   // 临界区: 三个字段连续读, 不被采样任务打断
    data.temperature = env.getTemperature();
    data.humidity    = env.getHumidity();
    data.soilPercent = soil.getMoisturePercent();
    portEXIT_CRITICAL(&criticalMux);
    data.timestamp   = millis();
    return data;
}

// 采样 + 打包一步完成(由 sensorTask 调用)
SensorData_t SensorService::updateAndGet() {
    update();               // 采样(内部 2s 节流)
    return getData();       // 打包返回
}

String SensorService::getSensorsJson() const {
    // 复用 getData(): 一次临界区快照, 保证 temperature/humidity/soil 来自同一次读取
    SensorData_t data = getData();
    String json = "{";
    if (!isnan(data.temperature) && !isnan(data.humidity)) {
        json += "\"temperature\":" + String(data.temperature, 1)
             + ",\"humidity\":" + String(data.humidity, 1);
    } else {
        json += "\"temperature\":null,\"humidity\":null";
    }
    json += ",\"soil\":" + String(data.soilPercent);
    json += "}";
    return json;
}
