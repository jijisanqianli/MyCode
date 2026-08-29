#include "ConfigService.h"
#include <LittleFS.h>

bool ConfigService::begin() {
    if (!LittleFS.exists(CONFIG_FILE)) {
        Serial.println("[CFG] no config file, use defaults");
        return false;
    }
    File file = LittleFS.open(CONFIG_FILE, "r");
    if (!file) {
        Serial.println("[CFG] open config failed");
        return false;
    }
    String json = file.readString();
    file.close();

    wifiSsid       = getStringField(json, "wifiSsid", wifiSsid);
    wifiPassword   = getStringField(json, "wifiPassword", wifiPassword);
    mqttBroker     = getStringField(json, "mqttBroker", mqttBroker);
    mqttPort       = getIntField(json, "mqttPort", mqttPort);
    mqttUsername   = getStringField(json, "mqttUsername", mqttUsername);
    mqttPassword   = getStringField(json, "mqttPassword", mqttPassword);
    dryThreshold   = getIntField(json, "dryThreshold", dryThreshold);
    wetThreshold   = getIntField(json, "wetThreshold", wetThreshold);
    defaultMode    = getStringField(json, "defaultMode", defaultMode);

    Serial.printf("[CFG] loaded: broker=%s dry=%d wet=%d mode=%s\n",
                  mqttBroker.c_str(), dryThreshold, wetThreshold, defaultMode.c_str());
    return true;
}

bool ConfigService::save() {
    File file = LittleFS.open(CONFIG_FILE, "w");
    if (!file) return false;
    file.print(toJson());
    file.close();
    Serial.println("[CFG] saved");
    return true;
}

String ConfigService::toJson() const {
    String json = "{";
    json += "\"wifiSsid\":\"" + wifiSsid + "\"";
    json += ",\"wifiPassword\":\"" + wifiPassword + "\"";
    json += ",\"mqttBroker\":\"" + mqttBroker + "\"";
    json += ",\"mqttPort\":" + String(mqttPort);
    json += ",\"mqttUsername\":\"" + mqttUsername + "\"";
    json += ",\"mqttPassword\":\"" + mqttPassword + "\"";
    json += ",\"dryThreshold\":" + String(dryThreshold);
    json += ",\"wetThreshold\":" + String(wetThreshold);
    json += ",\"defaultMode\":\"" + defaultMode + "\"";
    json += "}";
    return json;
}

bool ConfigService::updateFromJson(const String& json) {
    // 只更新消息中存在的字段, 缺省字段保持原值
    if (getField(json, "wifiSsid")     != "") wifiSsid     = getStringField(json, "wifiSsid", wifiSsid);
    if (getField(json, "wifiPassword") != "") wifiPassword = getStringField(json, "wifiPassword", wifiPassword);
    if (getField(json, "mqttBroker")   != "") mqttBroker   = getStringField(json, "mqttBroker", mqttBroker);
    if (getField(json, "mqttPort")     != "") mqttPort     = getIntField(json, "mqttPort", mqttPort);
    if (getField(json, "mqttUsername") != "") mqttUsername = getStringField(json, "mqttUsername", mqttUsername);
    if (getField(json, "mqttPassword") != "") mqttPassword = getStringField(json, "mqttPassword", mqttPassword);
    if (getField(json, "dryThreshold") != "") dryThreshold = getIntField(json, "dryThreshold", dryThreshold);
    if (getField(json, "wetThreshold") != "") wetThreshold = getIntField(json, "wetThreshold", wetThreshold);
    if (getField(json, "defaultMode")  != "") defaultMode  = getStringField(json, "defaultMode", defaultMode);

    return save();
}

// 提取 "key":value 的原始值(字符串去引号, 数字/布尔原样返回)
String ConfigService::getField(const String& json, const char* key) {
    String k = String("\"") + key + "\"";
    int pos = json.indexOf(k);
    if (pos < 0) return "";
    int colon = json.indexOf(':', pos);
    if (colon < 0) return "";

    int start = colon + 1;
    while (start < json.length() && json[start] == ' ') start++;
    if (start >= json.length()) return "";

    if (json[start] == '"') {   // 字符串值
        int end = json.indexOf('"', start + 1);
        if (end < 0) return "";
        return json.substring(start + 1, end);
    }
    // 数字/布尔值
    int end = start;
    while (end < json.length() && json[end] != ',' && json[end] != '}') end++;
    return json.substring(start, end);
}

String ConfigService::getStringField(const String& json, const char* key, const String& def) {
    String v = getField(json, key);
    return v.isEmpty() ? def : v;
}

int ConfigService::getIntField(const String& json, const char* key, int def) {
    String v = getField(json, key);
    return v.isEmpty() ? def : v.toInt();
}
