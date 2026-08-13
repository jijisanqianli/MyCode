# ESP32-S3 GPIO 引脚归类参考

> 本项目硬件：**ESP32-S3-DevKitC-1（8MB Flash + 8MB Octal PSRAM）**
> 接线前先查本表，避免引脚冲突。表内信息基于实测 + 芯片手册整理。

## 1. 引脚功能分类

### 1.1 模拟输入（ADC）

| 控制器 | 引脚范围 | 说明 |
|--------|---------|------|
| **ADC1** | GPIO1 ~ GPIO10 | ✅ 推荐使用，不受 WiFi 影响 |
| **ADC2** | GPIO11 ~ GPIO20 | ⚠️ **WiFi 开启时不可用**（与 WiFi 射频共用） |

> ⚠️ ADC2 是坑：正式程序连上 WiFi 后，ADC2 引脚 `analogRead` 返回异常。**模拟传感器必须接 ADC1**。

### 1.2 本板被占用的引脚（Octal PSRAM 配置）

`platformio.ini` 中 `memory_type = qio_opi`（Octal PSRAM），以下引脚被内存芯片占用，**不可作普通 IO**：

| 引脚 | 用途 |
|------|------|
| GPIO26 ~ 32 | Octal Flash 数据线 |
| **GPIO33 ~ 37** | **Octal PSRAM 数据线** ⚠️ |

> 💀 GPIO33~37 是本次 **boot loop 事故的元凶**：OLED 误用 GPIO35/36（PSRAM 数据线），`Wire.begin()` 破坏 PSRAM 内存，导致 WiFi 初始化崩溃、设备无限重启。

### 1.3 特殊功能引脚

| 引脚 | 功能 | 说明 |
|------|------|------|
| GPIO0 / 3 / 45 / 46 | Strapping 引脚 | 上电时序敏感，尽量避免 |
| GPIO19 / 20 | USB D- / D+ | USB 接口占用 |
| GPIO39 ~ 42 | JTAG | 通常不作为普通 IO |
| GPIO43 / 44 | UART0 TX / RX | 串口监视器占用，**别接外设** |
| GPIO48 | 板载 RGB LED | 已被板载灯占用，一般不用 |

## 2. 本项目引脚占用表

| 外设 | 引脚 | 类型 | 说明 |
|------|------|------|------|
| 灌溉通道 0 | **GPIO1** | 数字输出 | 电磁阀/继电器 |
| 灌溉通道 1 | **GPIO4** | 数字输出 | 电磁阀/继电器 |
| 灌溉通道 2 | **GPIO8** | 数字输出 | 电磁阀/继电器 |
| 土壤传感器（HW-390） | **GPIO2** | ADC1 模拟输入 | AO 输出，标定干 3290 / 湿 1057 |
| OLED（SSD1306） | **SDA=GPIO9, SCL=GPIO10** | I2C | 地址 0x3C，避开 PSRAM 区 |
| DHT22 温湿度 | **GPIO47** | 单总线输入 | DATA 线，2s 采样间隔 |

## 3. 空闲可用引脚（后续扩展参考）

| 类别 | 可用引脚 |
|------|---------|
| 模拟（ADC1） | GPIO3、5、6、7 |
| 普通数字 IO | GPIO15~18、21~25、38 |

> 注：GPIO15~18 属于 ADC2，WiFi 开启后不能做模拟输入，但可做数字 IO。

## 4. 接线避坑清单（血泪教训）

| 坑 | 原因 | 正确做法 |
|----|------|---------|
| OLED 接 GPIO35/36 后设备无限重启（`TG1WDT_SYS_RST`） | Octal PSRAM 占用 GPIO33~37，`Wire.begin(35,36)` 破坏 PSRAM | OLED 用 **GPIO9/10** |
| 土壤传感器接 GPIO39 报 `Pin 39 is not ADC pin` | GPIO39 不是 ADC 引脚 | 模拟传感器用 **ADC1（GPIO1~10）** |
| ADC2 引脚（11~20）读数异常 | WiFi 开启时 ADC2 不可用 | 模拟输入只用 **ADC1** |
| 外设接到 GPIO43/44 不工作 | 被 UART0（串口监视器）占用 | 避开 GPIO43/44 |
| 全部模拟引脚被占满 | 灌溉用了 1/4/8，土壤用 2 | 土壤改接 GPIO3/5/6/7 |

## 5. 与 lab 测试文件的对应

| lab 文件 | 使用的引脚 |
|----------|-----------|
| `src/lab/I2C_scan_test.cpp` | SDA=GPIO9, SCL=GPIO10 |
| `src/lab/OLED_display_test.cpp` | SDA=GPIO9, SCL=GPIO10（如有遗留 35/36 需同步修改） |
| `src/lab/dht_read_test.cpp` | DHT DATA=GPIO47 |
| `src/lab/soil_read_test.cpp` | AO=GPIO2 |
