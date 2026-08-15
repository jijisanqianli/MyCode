#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_SERVICE_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_SERVICE_H

#include "MqttDriver.h"
#include "SensorService.h"
#include "IrrigationService.h"

// MQTT 服务(Service 层): 编排云端通信
//  - 连接管理: 断线后定时重连, 连接成功后订阅控制主题
//  - 数据上报: 每 5s 发布传感器 JSON 到数据主题
//  - 指令下发: 收到 {"pump":"on"/"off","index":N} 时控制第 N 个灌溉通道
//    示例: {"pump":"on","index":0} 打开通道0, {"pump":"off","index":2} 关闭通道2
class MqttService {
    MqttDriver& mqttDriver;              // 底层通信(依赖注入)
    SensorService& sensorService;        // 数据来源(依赖注入)
    IrrigationService& irrigationService;  // 指令执行目标(依赖注入)

    const char* topicData;       // 数据上报主题
    const char* topicCmd;        // 指令下发主题
    const char* deviceId;        // 设备标识(写入上报 JSON)

    uint32_t lastPublishMs = 0;  // 上报节流时间戳
    uint32_t lastConnectMs = 0;  // 重连节流时间戳
    static constexpr uint32_t PUBLISH_INTERVAL_MS = 5000;  // 每 5s 上报一次
    static constexpr uint32_t CONNECT_RETRY_MS    = 3000;  // 断线每 3s 重连一次

    void onCommand(const String& topic, const String& payload);          // 解析并执行指令
    static void callbackBridge(const String& topic, const String& payload);  // 桥接 MqttDriver 回调
    static MqttService* instance;   // 单例指针: 静态桥接函数转发用

public:
    MqttService(MqttDriver& mqttDriver, SensorService& sensorService, IrrigationService& irrigationService,
                const char* deviceId, const char* topicData, const char* topicCmd);

    void begin();   // 注册回调(把 MqttDriver 的第二棒接到本服务)
    void update();  // 主循环调用: 重连 + 保活 + 周期上报
    void publishData();
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_SERVICE_H
