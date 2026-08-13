#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_OLED_DISPLAY_DRIVER_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_OLED_DISPLAY_DRIVER_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// SSD1306 OLED 显示屏驱动(128x64, I2C)
// 内置"内容缓存 + 最小刷新间隔": 内容没变不重绘(防闪烁),
// 两次绘制至少间隔 DRAW_INTERVAL_MS(节流, 避免高频调用拖慢主循环)。
//
// 注意引脚: 默认 SDA=9, SCL=10。
// 本板 Octal PSRAM(qio_opi)占用 GPIO33~37, 原 35/36 会被 PSRAM 占用,
// 用作 I2C 会破坏 PSRAM 导致 WiFi 初始化崩溃(boot loop)。
class OledDisplayDriver {
    Adafruit_SSD1306 display;
    uint8_t sdaPin;
    uint8_t sclPin;
    uint8_t i2cAddr;

    String cachedContent;              // 上次绘制的内容, 用于变化检测
    uint32_t lastDrawMs = 0;           // 节流时间戳
    static constexpr uint8_t  SCREEN_W = 128;
    static constexpr uint8_t  SCREEN_H = 64;
    static constexpr uint32_t DRAW_INTERVAL_MS = 500;

    void drawIfChanged(const String& content, uint8_t textSize = 1);   // 变化检测 + 节流
    void render(const String& content, uint8_t textSize = 1);    // 按行绘制(行距自适应)

public:
    // sda/scl: I2C 引脚(默认 GPIO9/10, 避开 PSRAM 占用的 GPIO33~37);
    // addr: 屏幕 I2C 地址(默认 0x3C)
    OledDisplayDriver(uint8_t sdaPin = 9, uint8_t sclPin = 10, uint8_t addr = 0x3C);

    bool begin();   // 初始化 I2C + 屏幕, 返回是否成功

    void showBoot(const char* line1, const char* line2 = nullptr);  // 启动页
    void showSensors(float temp, float hum, int soilPct);           // 传感器主页
    void showIrrigation(const bool* states, size_t count);          // 灌溉状态页
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_OLED_DISPLAY_DRIVER_H
