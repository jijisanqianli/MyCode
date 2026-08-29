#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WEB_SERVER_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WEB_SERVER_H

#include <WebServer.h>
#include "IrrigationService.h"
#include "SensorService.h"
#include "ConfigService.h"
#include "HistoryService.h"
#include <LittleFS.h>

class WebServerController {
    WebServer server;
    IrrigationService& irrigationService;
    SensorService& sensorService;
    ConfigService& configService;
    HistoryService& historyService;

    void setupRoutes();
    int parseChannelIndex();   // 解析 channel 参数,参数缺失或非法返回 -1

public:
    WebServerController(uint16_t port, IrrigationService& service, SensorService& sensors,
                        ConfigService& config, HistoryService& history);
    void begin();
    void handleClient();
};


#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WEB_SERVER_H
