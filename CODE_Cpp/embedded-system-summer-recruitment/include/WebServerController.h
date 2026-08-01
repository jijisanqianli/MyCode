#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WEB_SERVER_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WEB_SERVER_H

#include "WebServer.h"
#include "IrrigationService.h"
#include "LittleFS.h"

class WebServerController {
    WebServer server;
    IrrigationService& irrigationService;

    void setupRoutes();
    int parseChannelIndex();   // 解析 channel 参数,参数缺失或非法返回 -1

public:
    WebServerController(uint16_t port, IrrigationService& service);
    void begin();
    void handleClient();
};


#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_WEB_SERVER_H
