#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_DRIVER_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_DRIVER_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// 收到消息时的回调类型: 参数为 (主题, 消息内容)
// 以后所有“返回为空、带两个 String 参数的函数”，统统可以简称为 MqttCallback 这一种类型。
typedef void (*MqttCallback)(const String& topic, const String& payload);

// MQTT 驱动(Driver 层): 封装 PubSubClient + TLS
// 职责: 连接/发布/订阅/收消息回调, 不含任何业务逻辑。
class MqttDriver {
    WiFiClientSecure wifiClient;   // TLS 加密通道(Serverless 端口 8883)
    PubSubClient mqttClient;       // MQTT 协议客户端, 绑定上面的 TLS 通道
    String broker;                 // Broker 地址(如 xxxx.emqxsl.cn)
    uint16_t port;                 // 端口(8883)
    String clientId;               // 客户端唯一标识
    String username;               // 认证用户名
    String password;               // 认证密码

    static MqttDriver* instance;          // 单例指针: 静态回调借它转发消息
    MqttCallback userCallback = nullptr;  // 上层(Service)注册的业务回调

    static void onMessage(char* topic, byte* payload, unsigned int length);

public:
    MqttDriver(const char* broker, uint16_t port,
               const char* clientId, const char* username, const char* password);

    void begin();               // 一次性配置: TLS + 服务器地址 + 回调
    void setConfig(const char* broker, uint16_t port,
                   const char* username, const char* password);   // 运行期更新连接配置(配置服务用)
    bool connect();             // 连接 Broker, 返回是否成功
    void loop();                // 保活 + 处理收到的消息(放主循环高频调用)
    bool isConnected();   // 是否在线

    bool publish(const char* topic, const char* payload, bool retained = false);   // 发布消息(retained=保留消息)
    bool subscribe(const char* topic);                       // 订阅主题

    void setCallback(MqttCallback cb);   // 注册业务回调(由 Service 调用)
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_MQTT_DRIVER_H
