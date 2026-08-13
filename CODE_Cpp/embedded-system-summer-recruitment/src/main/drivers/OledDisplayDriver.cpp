#include "OledDisplayDriver.h"

OledDisplayDriver::OledDisplayDriver(uint8_t sda, uint8_t scl, uint8_t addr)
    : display(SCREEN_W, SCREEN_H, &Wire, -1),
      sdaPin(sda), sclPin(scl), i2cAddr(addr) {}

bool OledDisplayDriver::begin() {
    Wire.begin(sdaPin, sclPin);

    if (!display.begin(SSD1306_SWITCHCAPVCC, i2cAddr)) {
        return false;
    }
    display.setRotation(0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
    display.display();
    return true;
}

void OledDisplayDriver::showBoot(const char* line1, const char* line2) {
    String content = line1;
    if (line2 != nullptr) {
        content += "\n" + String(line2);
    }
    drawIfChanged(content);
}

void OledDisplayDriver::showSensors(float temp, float hum, int soilPct) {
    String content = String("T:") + String(temp, 1) + "C";
    content += "\nH:" + String(hum, 1) + "%";
    content += "\nSoil:" + String(soilPct) + "%";
    drawIfChanged(content, 2);   // 大号字体, 三排显示
}

void OledDisplayDriver::showIrrigation(const bool* states, size_t count) {
    String content = "Irrigation:";
    for (size_t i = 0; i < count; ++i) {
        content += "\nCH" + String(i) + " " + (states[i] ? "ON " : "OFF");
    }
    drawIfChanged(content);
}

void OledDisplayDriver::drawIfChanged(const String& content, uint8_t textSize) {
    // 内容没变 → 跳过重绘(防闪烁)
    if (content == cachedContent) return;

    // 节流: 两次绘制至少间隔 DRAW_INTERVAL_MS
    uint32_t now = millis();
    if (now - lastDrawMs < DRAW_INTERVAL_MS) return;

    lastDrawMs = now;
    cachedContent = content;
    render(content, textSize);
}

void OledDisplayDriver::render(const String& content, uint8_t textSize) {
    display.clearDisplay();
    display.setTextSize(textSize);

    // 按 '\n' 分行, 行距自适应字号(textSize 1 → 10px 行高, textSize 2 → 18px)
    int lineHeight = 8 * textSize + 2;
    int y = 0;
    int idx = 0;
    while (idx < (int)content.length()) {
        int nl = content.indexOf('\n', idx);
        String line = (nl < 0) ? content.substring(idx) : content.substring(idx, nl);
        display.setCursor(0, y);
        display.println(line);
        y += lineHeight;
        if (nl < 0) break;
        idx = nl + 1;
    }
    display.display();
}
