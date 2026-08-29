#include "HistoryService.h"

void HistoryService::add(const SensorData_t& data) {
    // 降频节流: 每 SAMPLE_INTERVAL_MS 才存一条
    uint32_t now = millis();
    if (now - lastAddMs < SAMPLE_INTERVAL_MS) return;
    lastAddMs = now;

    buffer[head] = data;
    head = (head + 1) % MAX_POINTS;
    if (count < MAX_POINTS) count++;
}

size_t HistoryService::getCount() const {
    return count;
}

String HistoryService::toJson(size_t limit) const {
    if (limit > count) limit = count;

    // 环形缓冲最旧元素位置
    size_t start = (head + MAX_POINTS - count) % MAX_POINTS;

    String json = "[";
    for (size_t i = 0; i < limit; ++i) {
        if (i > 0) json += ",";
        const SensorData_t& d = buffer[(start + i) % MAX_POINTS];
        json += "{\"ts\":" + String(d.timestamp)
              + ",\"t\":" + String(d.temperature, 2)
              + ",\"h\":" + String(d.humidity, 2)
              + ",\"s\":" + String(d.soilPercent) + "}";
    }
    json += "]";
    return json;
}
