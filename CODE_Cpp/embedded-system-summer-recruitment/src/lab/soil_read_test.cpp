#include "common_config.h"
#include <Arduino.h>

// 接线: HW-390(电容式土壤湿度传感器)
//       VCC -> 3.3V | GND -> GND | AO -> GPIO2
//       (DO 是板载比较器的数字输出, 本测试不使用)
//
// 实测标定(2026-08-12, 本机这块板):
//   悬空(干燥空气): raw = 3290 (2.651V)
//   浸水(湿)      : raw = 1057 (0.852V)
//   方向: 越湿读数越低
//   公式: 湿度% = (3290 - raw) * 100 / (3290 - 1057), 限幅到 0~100
//   例  : raw = 2500 -> (3290-2500)/2233 ≈ 35%
#define SOIL_PIN     2
#define SAMPLE_COUNT 20     // 采样次数, 取平均抗 ADC 抖动
#define SOIL_DRY     3290   // 标定: 悬空干燥基准
#define SOIL_WET     1057   // 标定: 浸水基准

// 连续采样 SAMPLE_COUNT 次取平均, 减少 ADC 抖动
int readSoilRaw() {
    long sum = 0;
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        sum += analogRead(SOIL_PIN);
        delay(5);
    }
    return (int)(sum / SAMPLE_COUNT);
}

void setup() {
    Serial.begin(SYSTEM_BAUD_RATE);
    delay(1000);
    printSystemHeader("HW-390 SOIL TEST");

    // ESP32-S3: 打开引脚衰减以覆盖 0~3.3V 量程(否则读数会提前截顶)
    analogSetPinAttenuation(SOIL_PIN, ADC_11db);
    pinMode(SOIL_PIN, INPUT);

    Serial.printf("HW-390 on GPIO%d (ADC)\n", SOIL_PIN);
    Serial.println("标定方法: 依次记录下面三种状态的读数(raw 与 voltage)");
    Serial.println("  air   : 传感器悬空/干燥空气中");
    Serial.println("  water : 完全浸入水中");
    Serial.println("  plant : 插入正常湿度的花盆土");
    Serial.println("注意: 不同批次板子输出方向可能相反(越湿越高或越湿越低)");
    Serial.println("----------------------------------------");
}

void loop() {
    delay(2000);

    int raw = readSoilRaw();
    float voltage = raw * (3.3f / 4095.0f);  // ESP32-S3 ADC 为 12 位

    // 标定公式: 越湿读数越低, (干 - raw) / (干 - 湿) 映射到 0~100%
    int pct = (SOIL_DRY - raw) * 100 / (SOIL_DRY - SOIL_WET);
    if (pct < 0)   pct = 0;
    if (pct > 100) pct = 100;

    Serial.printf("raw=%d | voltage=%.3f V | soil=%d%%\n", raw, voltage, pct);
}
