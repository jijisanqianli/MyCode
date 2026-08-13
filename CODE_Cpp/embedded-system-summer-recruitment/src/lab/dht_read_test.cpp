#include "common_config.h"
#include <DHT.h>

// 接线: DHT22 的 DATA 引脚 -> GPIO47
//       VCC -> 3.3V(或 5V,看模块标识), GND -> GND
//       若模块不自带上拉, 需要在 DATA 与 VCC 间接 4.7k~10k 上拉电阻
//
// 实测(2026-08-12): Temperature: 27.1 C | Humidity: 64.4 %  读数正常
#define DHT_PIN  47
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(SYSTEM_BAUD_RATE);
    delay(1000);
    printSystemHeader("DHT22 READ TEST");

    dht.begin();
    Serial.printf("DHT sensor on GPIO%d, sampling every 2s\n", DHT_PIN);
    Serial.println("(DHT22 数据手册要求两次采样间隔 >= 2s)");
    Serial.println("----------------------------------------");
}

void loop() {
    // 节流: 满足 DHT22 的采样间隔要求, 这里用 delay 简单实现
    delay(2000);

    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature();  // 默认返回摄氏度

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("ERROR: failed to read DHT sensor!");
        Serial.println("Check: wiring / power supply / pull-up resistor");
        return;
    }

    Serial.printf("Temperature: %.1f C | Humidity: %.1f %%\n", temperature, humidity);
}
