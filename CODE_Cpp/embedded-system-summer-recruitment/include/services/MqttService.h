#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_SERVICE_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_SERVICE_H

#include "MqttDriver.h"
#include "SensorService.h"
#include "IrrigationService.h"
#include "TaskConfig.h"

// MQTT 服务(Service 层): 编排云端通信
//  - 连接管理: 断线后定时重连, 连接成功后订阅控制主题
//  - 指令下发: 收到 {"pump":"on"/"off","index":N} / {"mode":"auto"/"manual"}
//              解析后发 manualIrrQueue(控制权收敛到 controlTask)
//  - 数据上报: 由 mqttTask 驱动, 传入 SensorData_t 拼 JSON(含 mode)
class MqttService {
    MqttDriver& mqttDriver;
    // [任务化] 不再直接使用, 保留构造签名以兼容组装; 数据经结构体/队列传递
    SensorService& sensorService;
    IrrigationService& irrigationService;

    const char* topicData;       // 数据上报主题
    const char* topicCmd;        // 指令下发主题
    const char* deviceId;        // 设备标识(写入上报 JSON)

    uint32_t lastConnectMs = 0;  // 重连节流时间戳
    static constexpr uint32_t CONNECT_RETRY_MS = 3000;  // 断线每 3s 重连一次

    void onCommand(const String& topic, const String& payload);          // 解析指令 → 发 manualIrrQueue
    static void callbackBridge(const String& topic, const String& payload);  // 桥接 MqttDriver 回调
    static MqttService* instance;   // 单例指针: 静态桥接函数转发用

public:
    MqttService(MqttDriver& mqttDriver, SensorService& sensorService, IrrigationService& irrigationService,
                const char* deviceId, const char* topicData, const char* topicCmd);

    void begin();   // 注册回调
    void update();  // 连接/重连/保活/收指令(上报由 mqttTask 驱动)
    bool isConnected();
    void publishData(const SensorData_t& data);   // 拼 JSON(含 mode)并上报
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_SERVICE_H
