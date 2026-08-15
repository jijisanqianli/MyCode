// 框架库在 src 显式 include, 让 LDF 检测到依赖
// (头文件在 include/ 子目录时 LDF 不会继续追踪其中的库 include)
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "MqttDriver.h"

// 静态成员定义(整个程序唯一)
MqttDriver* MqttDriver::instance = nullptr;

// 构造函数: 把 PubSubClient 绑定到 TLS 客户端, 并保存连接配置
MqttDriver::MqttDriver(const char* broker, uint16_t port,
                       const char* clientId, const char* username, const char* password)
    : mqttClient(wifiClient),     // 关键: PubSubClient 必须绑定一个网络客户端
      broker(broker), port(port),
      clientId(clientId), username(username), password(password) {}

void MqttDriver::begin() {
    // ① TLS: 跳过证书校验(免去下载证书嵌入)。
    //    正规做法: 下载 EMQX Cloud 的 CA 证书, 换成 wifiClient.setCACert(caCert);
    wifiClient.setInsecure();

    // ② 设置 Broker 地址与端口
    mqttClient.setServer(broker.c_str(), port);

    // ③ 注册静态回调, 并记录单例指针供回调转发
    mqttClient.setCallback(MqttDriver::onMessage);
    instance = this;
}

// 连接: 已连接则不重复连接(幂等), 返回当前是否在线
bool MqttDriver::connect() {
    if (!mqttClient.connected()) {
        mqttClient.connect(clientId.c_str(), username.c_str(), password.c_str());
    }
    return mqttClient.connected();
}

void MqttDriver::loop() {
    mqttClient.loop();   // 库要求: 高频调用以维持心跳 + 触发消息回调
}

bool MqttDriver::isConnected() {
    return mqttClient.connected();
}

bool MqttDriver::publish(const char* topic, const char* payload) {
    return mqttClient.publish(topic, payload);
}

bool MqttDriver::subscribe(const char* topic) {
    return mqttClient.subscribe(topic);
}

// Service 通过这个方法把"收到消息后干什么"挂进来, Driver 不关心内容
// 这个是提供给 Service 的注册入口，Driver层本身不使用该函数
void MqttDriver::setCallback(MqttCallback cb) {
    userCallback = cb;
}

// PubSubClient 要求回调必须是静态函数(不能是成员函数)。
// 这里通过单例指针 instance 把消息转发给上层注册的业务回调。
// 是实际上被 PubSubClient 回调调用的函数。
void MqttDriver::onMessage(char* topic, byte* payload, unsigned int length) {
    if (instance != nullptr && instance->userCallback != nullptr) {
        // String((char*)payload, length): 按长度构造, 防止消息中含 \0 被截断
        instance->userCallback(String(topic), String((char*)payload, length));
    }
}
