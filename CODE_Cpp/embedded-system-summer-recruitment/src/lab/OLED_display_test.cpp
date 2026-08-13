#include <Adafruit_SSD1306.h>  // 1. 改为 SSD1306 驱动库
#include <Wire.h>              // I2C 通信库

// I2C 引脚定义
// 注意: 本板 Octal PSRAM(qio_opi)占用 GPIO33~37, 原 35/36 不能用作 I2C(会破坏 PSRAM 导致 WiFi 崩溃)
#define SDA_PIN 9      // 数据线
#define SCL_PIN 10     // 时钟线
#define OLED_RESET -1  // 复位引脚（若没有硬件复位脚填 -1）

// 2. 修正屏幕分辨率（SSD1306 最常见为 128x64，若为 128x32 请修改高为 32）
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// 创建显示器对象
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    // 初始化 I2C 总线
    Wire.begin(SDA_PIN, SCL_PIN);

    Serial.begin(9600);
    delay(1000);
    Serial.println("SSD1306 OLED test");

    // 3. 修改初始化函数：传入 SSD1306_SWITCHCAPVCC 供电模式，I2C 地址通常为 0x3C
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("Unable to initialize OLED"));
        while (1) yield();
    }

    // 显示设置
    display.clearDisplay();
    display.setRotation(0);  // 旋转角度 (0, 1, 2, 3)，可根据模组安装方向调整
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);  // 4. 替换为 SSD1306 的颜色常量

    // 显示文本
    display.setCursor(10, 5);
    display.println("Hello,");
    display.setCursor(40, 25);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // 白底黑字反色显示
    display.println(" World!");
    display.display();

    delay(1000);
}

void loop() {
}
