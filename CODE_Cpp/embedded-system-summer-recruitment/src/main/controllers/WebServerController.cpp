// 框架库在 src 显式 include, 让 LDF 能检测到依赖
// (头文件在 include/ 子目录时 LDF 不会继续追踪其中的框架库 include)
#include <WebServer.h>
#include <LittleFS.h>
#include <Update.h>
#include "WebServerController.h"
#include "IrrigationService.h"
#include "TaskConfig.h"
#include <ctype.h>

// ===== OTA 更新 =====
// 上传密钥(自行修改): 页面提交时拼到 URL ?key=xxx
static const char* OTA_KEY = "ota2026";

// OTA 上传页面(内嵌, 无需文件系统文件)
static const char OTA_PAGE_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html lang="zh-CN"><head><meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP32 OTA 更新</title></head>
<body style="font-family:'Microsoft YaHei',Arial,sans-serif;text-align:center;margin-top:50px;">
<h2>📡 ESP32 固件更新</h2>
<p style="color:#888;font-size:13px;">上传 .bin 固件，完成后设备自动重启</p>
<form method="POST" action="/update" enctype="multipart/form-data" onsubmit="return prepSubmit()">
  <p><input type="file" name="update" accept=".bin" required></p>
  <p><input type="password" id="pwd" placeholder="更新密钥" required></p>
  <p><button type="submit" style="padding:10px 30px;font-size:16px;">上传并更新</button></p>
</form>
<p style="color:#c00;font-size:12px;">⚠️ 更新期间请勿断电，失败会自动回滚到旧固件</p>
<script>
function prepSubmit() {
  document.querySelector('form').action = '/update?key=' + document.getElementById('pwd').value;
  return true;
}
</script>
</body></html>
)rawliteral";

WebServerController::WebServerController(uint16_t port, IrrigationService& service, SensorService& sensors,
                                         ConfigService& config, HistoryService& history):
    server(port), irrigationService(service), sensorService(sensors),
    configService(config), historyService(history){}

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

    // 纯 MQTT 控制页面(WebSocket 直连 Broker, 不走 ESP32 HTTP API)
    server.on("/irrigation-mqtt", HTTP_GET, [this]() {
        File file = LittleFS.open("/irrigation-mqtt.html", "r");
        if (!file) {
            server.send(404, "text/plain", "File Not Found");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    // ===== [阶段C] OTA 远程更新 =====
    // 上传页面
    server.on("/update", HTTP_GET, [this]() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", OTA_PAGE_HTML);
    });

    // 固件上传: 完成回调 + 分块写入回调
    server.on("/update", HTTP_POST,
        [this]() {   // 上传完成
            server.sendHeader("Connection", "close");
            if (Update.hasError()) {
                server.send(500, "text/plain", "Update FAILED");
            } else {
                server.send(200, "text/plain", "Update OK, rebooting...");
                delay(500);
                ESP.restart();
            }
        },
        [this]() {   // 分块接收
            HTTPUpload& upload = server.upload();
            if (upload.status == UPLOAD_FILE_START) {
                // 密钥校验(URL 参数 ?key=xxx)
                if (server.arg("key") != OTA_KEY) {
                    Serial.println("[OTA] auth failed");
                    Update.abort();
                    return;
                }
                Serial.printf("[OTA] Start: %s\n", upload.filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
                    Update.printError(Serial);
                }
            } else if (upload.status == UPLOAD_FILE_WRITE) {
                if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                    Update.printError(Serial);
                }
            } else if (upload.status == UPLOAD_FILE_END) {
                if (Update.end(true)) {   // 校验并切换固件
                    Serial.printf("[OTA] Success: %u bytes\n", upload.totalSize);
                } else {
                    Update.printError(Serial);
                }
            }
        }
    );

    // [阶段D] 历史数据(时间序列, 供前端曲线绘制): /api/history?limit=N
    server.on("/api/history", HTTP_GET, [this]() {
        size_t limit = 120;
        if (server.arg("limit").length() > 0) {
            limit = server.arg("limit").toInt();
        }
        server.send(200, "application/json", historyService.toJson(limit));
    });

    // 获取传感器数据(温度/湿度/土壤/模式), 数据由 SensorService 周期采样缓存
    server.on("/api/sensors", HTTP_GET, [this]() {
        String json = sensorService.getSensorsJson();
        // 在返回 JSON 尾部追加当前控制模式: {"temperature":..,"soil":..,"mode":"auto"}
        json = json.substring(0, json.length() - 1);
        json += ",\"mode\":\"" + String(controlMode == MODE_MANUAL ? "manual" : "auto") + "\"}";
        server.send(200, "application/json", json);
    });

    // 切换控制模式(手动/自动): 指令也发 manualIrrQueue, 执行权收敛到 controlTask
    server.on("/irrigation/mode", HTTP_POST, [this]() {
        String mode = server.arg("mode");
        if (mode != "auto" && mode != "manual") {
            server.send(400, "text/plain", "mode must be auto or manual");
            return;
        }
        Command_t cmd;
        cmd.index  = 0;
        cmd.pumpOn = false;
        cmd.mode   = (mode == "auto") ? MODE_AUTO : MODE_MANUAL;
        if (manualIrrQueue != nullptr) {
            xQueueSend(manualIrrQueue, &cmd, 0);
        }
        server.send(200, "text/plain", "mode switch requested: " + mode);
    });

    // [阶段B] 读取持久化配置(WiFi/MQTT/阈值/默认模式)
    server.on("/api/config", HTTP_GET, [this]() {
        server.send(200, "application/json", configService.toJson());
    });

    // [阶段B] 更新持久化配置(只更新消息中存在的字段), WiFi/MQTT 变更需重启生效
    server.on("/api/config", HTTP_POST, [this]() {
        String body = server.arg("plain");
        if (body.length() == 0) {
            server.send(400, "text/plain", "empty config body");
            return;
        }
        if (configService.updateFromJson(body)) {
            server.send(200, "text/plain", "config saved, reboot to apply");
        } else {
            server.send(400, "text/plain", "config parse/save failed");
        }
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
        // [任务化] 控制收敛: 指令发 manualIrrQueue, 由 controlTask 唯一执行
        Command_t cmd;
        cmd.index  = (uint8_t)index;
        cmd.pumpOn = true;
        cmd.mode   = -1;   // pump 指令 → controlTask 自动切手动模式
        if (manualIrrQueue != nullptr) {
            xQueueSend(manualIrrQueue, &cmd, 0);
        }
        server.send(200, "text/plain", String("Irrigation start requested (channel ") + index + ")");
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
        // [任务化] 控制收敛: 指令发 manualIrrQueue, 由 controlTask 唯一执行
        Command_t cmd;
        cmd.index  = (uint8_t)index;
        cmd.pumpOn = false;
        cmd.mode   = -1;
        if (manualIrrQueue != nullptr) {
            xQueueSend(manualIrrQueue, &cmd, 0);
        }
        server.send(200, "text/plain", String("Irrigation stop requested (channel ") + index + ")");
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
