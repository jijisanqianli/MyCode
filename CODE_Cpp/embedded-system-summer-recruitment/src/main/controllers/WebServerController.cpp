// 框架库在 src 显式 include, 让 LDF 能检测到依赖
// (头文件在 include/ 子目录时 LDF 不会继续追踪其中的框架库 include)
#include <WebServer.h>
#include <LittleFS.h>
#include "WebServerController.h"
#include "IrrigationService.h"
#include <ctype.h>

WebServerController::WebServerController(uint16_t port, IrrigationService& service, SensorService& sensors):
    server(port), irrigationService(service), sensorService(sensors){}

void WebServerController::setupRoutes() {
    // 获取主页
    server.on("/irrigation", HTTP_GET, [this]() {
        File file = LittleFS.open("/irrigation.html", "r");
        if (!file) {
            server.send(404, "text/plain", "File Not Found");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    // 获取传感器数据(温度/湿度/土壤), 数据由 SensorService 周期采样缓存
    server.on("/api/sensors", HTTP_GET, [this]() {
        server.send(200, "application/json", sensorService.getSensorsJson());
    });

    // 获取通道列表
    server.on("/irrigation/channels", HTTP_GET, [this]() {
        String json = "[";
        size_t count = irrigationService.getChannelCount();
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) json += ",";
            const IrrigationChannel& ch = irrigationService.getChannel(i);
            json += String("{\"index\":") + i
                  + ",\"gpioPin\":" + ch.gpioPin
                  + ",\"name\":\"" + ch.name + "\"}";
        }
        json += "]";
        server.send(200, "application/json", json);
    });

    // 启动指定通道灌溉
    server.on("/irrigation/on", HTTP_POST, [this]() {
        int index = parseChannelIndex();
        if (index < 0) {
            server.send(400, "text/plain", "Missing or invalid channel parameter");
            return;
        }
        if ((size_t)index >= irrigationService.getChannelCount()) {
            server.send(404, "text/plain", "Channel not found");
            return;
        }
        if (irrigationService.turnOnIrrigation(index)) {
            server.send(200, "text/plain", String("Irrigation started (channel ") + index + ")");
        } else {
            server.send(409, "text/plain", "Channel already running");
        }
    });

    // 停止指定通道灌溉
    server.on("/irrigation/off", HTTP_POST, [this]() {
        int index = parseChannelIndex();
        if (index < 0) {
            server.send(400, "text/plain", "Missing or invalid channel parameter");
            return;
        }
        if ((size_t)index >= irrigationService.getChannelCount()) {
            server.send(404, "text/plain", "Channel not found");
            return;
        }
        if (irrigationService.turnOffIrrigation(index)) {
            server.send(200, "text/plain", String("Irrigation stopped (channel ") + index + ")");
        } else {
            server.send(409, "text/plain", "Channel not running");
        }
    });

    // 获取状态:无 channel 参数返回全部通道数组,带 channel 参数返回单通道对象
    server.on("/irrigation/status", HTTP_GET, [this]() {
        if (server.arg("channel").length() == 0) {
            server.send(200, "application/json", irrigationService.getAllStatusJson());
            return;
        }
        int index = parseChannelIndex();
        if (index < 0) {
            server.send(400, "text/plain", "Missing or invalid channel parameter");
            return;
        }
        if ((size_t)index >= irrigationService.getChannelCount()) {
            server.send(404, "text/plain", "Channel not found");
            return;
        }
        server.send(200, "application/json", irrigationService.getStatusJson(index));
    });
}

// 解析 channel 参数:缺失或含非数字字符返回 -1(对应 400);
// 数字越界由调用方用 getChannelCount() 判断(对应 404)。
int WebServerController::parseChannelIndex() {
    String arg = server.arg("channel");
    if (arg.length() == 0) return -1;
    //校验是否为数字
    for (size_t i = 0; i < arg.length(); ++i) {
        if (!isdigit((unsigned char)arg[i])) return -1;
    }
    return arg.toInt();
}

void WebServerController::begin() {
    setupRoutes();
    server.begin();
    Serial.println("HTTP server started");
}

void WebServerController::handleClient() {
    server.handleClient();
}
