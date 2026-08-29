#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_CONFIG_SERVICE_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_CONFIG_SERVICE_H

#include <Arduino.h>

// 配置服务: 用 LittleFS 持久化系统配置(/config.json)
// 覆盖: WiFi / MQTT / 灌溉阈值 / 默认模式
// 扁平 JSON 结构(手动解析, 不引入 JSON 库):
//   {"wifiSsid":"..","wifiPassword":"..","mqttBroker":"..","mqttPort":8883,
//    "mqttUsername":"..","mqttPassword":"..","dryThreshold":30,"wetThreshold":60,
//    "defaultMode":"auto"}
class ConfigService {
    static constexpr const char* CONFIG_FILE = "/config.json";

public:
    // 当前配置(默认值 = 编译期硬编码, 可被 /config.json 覆盖)
    String   wifiSsid       = "SDK";
    String   wifiPassword   = "13730708827";
    String   mqttBroker     = "i3daab3b.ala.cn-shenzhen.emqxsl.cn";
    uint16_t mqttPort       = 8883;
    String   mqttUsername   = "esp32-s3";
    String   mqttPassword   = "123654789";
    int      dryThreshold   = 30;
    int      wetThreshold   = 60;
    String   defaultMode    = "auto";

    bool begin();            // 读取配置(文件不存在则保留默认值)
    bool save();             // 保存到 /config.json
    String toJson() const;   // 当前配置 → JSON
    bool updateFromJson(const String& json);   // 解析 JSON 更新配置并保存

private:
    static String getField(const String& json, const char* key);   // 提取 "key":value 原始值
    static String getStringField(const String& json, const char* key, const String& def);
    static int    getIntField(const String& json, const char* key, int def);
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_CONFIG_SERVICE_H
