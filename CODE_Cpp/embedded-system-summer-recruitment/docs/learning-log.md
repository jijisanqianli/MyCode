# 学习日志

## Day 1

### 今日完成

#### 1. Arduino IDE 安装与配置

- 下载并安装 Arduino IDE
- 配置 ESP32 开发板支持（通过开发板管理器添加 ESP32 平台）
- 完成开发板与电脑的连接测试

#### 2. 第一个程序：Hello World

成功运行串口输出程序，实现 PC 端串口监视器显示 "Hello World!"。

**代码：**

```cpp
void setup() {
  // 在此处的代码会运行一次：
  Serial.begin(9600);  // 初始化串口通信，设置波特率为 9600
  while (!Serial){
    ; // 等待串口连接建立
  };
  Serial.println("Hello World!");  // 通过串口发送字符串 "Hello World!" 并换行
}

void loop() {
  // 在此处的代码会一直重复运行：
}
```

**关键知识点：**

| 概念 | 说明 |
|-----|------|
| `Serial.begin(9600)` | 初始化串口通信，波特率设为 9600 bps |
| `while (!Serial)` | 等待串口连接就绪（Leonardo/ESP32 等需要） |
| `Serial.println()` | 通过串口发送字符串并自动换行 |
| `setup()` | 在开发板开机或复位后只执行一次，用于初始化设置。常用于初始化串口通信、设置引脚模式、初始化传感器和模块等 |
| `loop()` | `setup()` 执行完毕后，`loop()` 函数会无限循环执行，是程序的主体部分 |

**串口通信详解：**

| 函数/概念 | 说明 |
|----------|------|
| `Serial` | 预定义对象，代表开发板的硬件串口或 USB 虚拟串口。在 ESP32-S3 上通常指通过 USB 连接创建的虚拟串口，用于与电脑进行文本数据收发 |
| `Serial.begin(9600)` | 初始化串口通信并设置波特率（常用 9600、115200）。代码波特率必须与串口监视器设置一致，否则会显示乱码 |
| `while (!Serial)` | 等待串口连接就绪。连接建立前 `Serial` 布尔值为 `false`，连接建立（如打开串口监视器）后变为 `true`，确保连接稳定后再发送数据 |
| `Serial.println(data)` | 发送数据（字符串、变量、数字等）到串口并自动换行 |
| `Serial.print(data)` | 发送数据到串口但不自动换行（与 `println` 的区别） |
| `delay(ms)` | 暂停程序执行指定毫秒数，用于控制时间间隔（如 LED 闪烁频率） |

**运行结果：** ✅ 成功

串口监视器正确显示：
```
Hello World!
```

---

### 踩坑记录

| 问题 | 原因 | 解决方案 |
|-----|------|---------|
| 串口监视器出现 `R~gB` 乱码，且 `Serial.println("Hello World!");` 完全没有输出 | 初次通过 COM 接口连接，却开启了 USB CDC ON BOOT | 重新通过 USB 接口连接开发板 |

#### 3. GPIO 与数字信号基础

**数字信号本质：**

用离散的电压状态传递信息，ESP32 GPIO 使用二进制数字信号：

| 状态 | 逻辑值 | 电压 | 类比 |
|-----|-------|------|------|
| 高电平 (HIGH) | 1 / 真 | ≈ 3.3V | 开关打开 |
| 低电平 (LOW) | 0 / 假 | ≈ 0V (GND) | 开关闭合 |

**GPIO 两种工作模式：**

| 模式 | 方向 | 作用 | 应用场景 |
|-----|------|------|---------|
| 输出模式 | ESP32 → 外设 | 控制引脚高低电平（"说话"） | 控制 LED 开关 |
| 输入模式 | 外设 → ESP32 | 检测引脚电平状态（"倾听"） | 检测按钮是否按下 |

#### 4. WiFi 扫描程序

成功扫描并显示周围 Wi-Fi 网络信息（SSID、信号强度、信道、加密类型）。

**核心 API：**

| 函数 | 说明 |
|-----|------|
| `WiFi.mode(WIFI_STA)` | 设置为站点模式 |
| `WiFi.disconnect()` | 断开已有连接，确保未连接状态 |
| `WiFi.scanNetworks()` | 同步扫描周围网络，阻塞式，返回网络数量 |
| `WiFi.SSID(i)` | 获取第 i 个网络的名称 |
| `WiFi.RSSI(i)` | 获取信号强度（dBm，负数，越接近 0 越强） |
| `WiFi.channel(i)` | 获取所在信道 |
| `WiFi.encryptionType(i)` | 获取加密类型（WPA2、WPA3 等） |
| `WiFi.scanDelete()` | 删除扫描结果释放内存 |

#### 5. WiFi 连接

成功连接到指定 Wi-Fi 网络并获取 IP 地址。

**核心流程：**

```cpp
WiFi.mode(WIFI_STA);           // 设置站点模式
WiFi.begin(ssid, password);    // 连接网络
while (WiFi.status() != WL_CONNECTED) { delay(500); }  // 等待连接
WiFi.localIP();                // 获取 IP 地址
```

**关键 API：**

| 函数 | 说明 |
|-----|------|
| `WiFi.begin(ssid, password)` | 异步函数，启动连接后立即返回，连接在后台进行 |
| `WiFi.status()` | 获取连接状态，`WL_CONNECTED` 表示已连接 |
| `WiFi.localIP()` | 获取 DHCP 分配的 IP 地址，类型为 IPAddress |

**常见 Wi-Fi 状态值：**

| 状态 | 说明 |
|-----|------|
| `WL_IDLE_STATUS` | Wi-Fi 处于空闲状态 |
| `WL_NO_SSID_AVAIL` | 找不到指定的网络名称 |
| `WL_CONNECTED` | 已成功连接 |
| `WL_CONNECT_FAILED` | 连接失败 |
| `WL_CONNECTION_LOST` | 连接丢失 |

**运行结果：** ✅ 成功

```
Connecting to SDK
.........
WiFi connected.
IP address: 
192.168.1.18
```

**关于循环中 `delay(500)` 的作用：**

Wi-Fi 建立连接需要扫描信道 → 握手校验 → 获取 IP（DHCP）等复杂网络交互，通常需要 1~3 秒。`WiFi.status()` 只是状态查询，不会阻塞等待连接完成。若不加 `delay(500)`，while 循环会以微秒级速度每秒轮询几百万次，不仅消耗性能，还会导致串口瞬间喷出大量 `.` 造成卡死。

#### 6. 开发环境迁移

经过实际使用，Arduino IDE 存在以下不足：

| 问题 | 说明 |
|-----|------|
| 多文件管理困难 | 项目结构不清晰，难以组织大型项目 |
| Git 版本管理不便 | 无法很好地与 Git 配合进行版本控制 |

**最终方案：CLion + PlatformIO**

- **CLion**：JetBrains 出品的 C/C++ IDE，强大的代码编辑、重构和调试功能
- **PlatformIO**：嵌入式开发插件，支持多平台、多框架，原生支持项目结构管理和 Git 集成

---

### 今日总结

- [x] 完成 Arduino IDE 安装配置
- [x] 运行第一个 Hello World 程序
- [x] 扫描周围 Wi-Fi 网络
- [x] 成功连接 Wi-Fi 网络
- [x] 开发环境迁移至 CLion + PlatformIO

---

## Day 2

### 今日完成

#### 1. 项目结构优化

重新组织项目目录结构，实现项目与练习分离：

```
src/
├── main/          ← 整体项目文件
└── lab/           ← 小独立练习、测试文件
```

通过 `platformio.ini` 配置文件实现环境分离构建，结构更清晰，利于学习和管理。

**配置文件示例：**

```ini
; 正式程序
[env:app-main]
build_src_filter =
    -<*>
    +<main/>

; 实验 1：hello_world
[env:lab-hello_world]
build_src_filter =
    -<*>
    +<lab/hello_world.cpp>
```

#### 2. GPIO 控制 LED 闪烁

**引脚与 GPIO 概念：**

引脚（Pin）是从芯片或电子元件内部电路引出与外围电路接线的接口。GPIO（General-purpose input/output）引脚负责输入/输出电压，开发板上以 D 开头的引脚（如 D2、D4、D15）都是 GPIO 引脚。

通过 ESP32-S3 的 GPIO 控制 LED 实现 1 秒一次的闪烁。

**关键 API：**

| 函数/概念 | 说明 |
|----------|------|
| `const int ledPin = 4` | 定义常量，程序运行期间不可变，便于统一管理引脚 |
| `pinMode(ledPin, OUTPUT)` | 配置引脚工作模式，OUTPUT 为输出模式，ESP32 可控制该引脚输出高低电平 |
| `digitalWrite(ledPin, HIGH)` | 向引脚输出电平，HIGH 为 3.3V（LED 点亮），LOW 为 0V（LED 熄灭） |
| `delay(1000)` | 暂停程序 1000 毫秒（1秒），期间程序不执行其他操作，无法响应其他事件 |

**常用 Arduino API：**

| 函数 | 说明 |
|-----|------|
| `analogRead(pin)` | 读取模拟引脚上的值（0-1023） |
| `analogWrite(pin, value)` | 在支持 PWM 的引脚上输出模拟值（0-255） |
| `Serial.begin(baud)` | 初始化串口通信，设置波特率 |
| `Serial.println(data)` | 将数据打印到串口监视器 |

#### 3. WebServer 基础

在 ESP32 上创建 HTTP 服务器，实现网页访问。

**核心 API：**

| 函数/概念 | 说明 |
|----------|------|
| `#include <WebServer.h>` | 引入 Web Server 库，用于创建 HTTP 服务器 |
| `WebServer server(80)` | 创建服务器对象，监听 HTTP 默认端口 80 |
| `server.on("/", handleRoot)` | 注册路由处理函数，访问根路径 "/" 时调用 handleRoot()。类似于后端的 Controller 层，将请求路径与处理函数绑定 |
| `server.onNotFound(handleNotFound)` | 注册 404 处理函数，当访问不存在的路径时调用 |
| `server.arg(name)` | 获取 URL 查询参数或表单提交的值，name 为参数名 |
| `server.begin()` | 启动服务器，开始监听客户端连接请求 |
| `server.handleClient()` | 在 loop() 中持续调用，处理传入的客户端请求 |
| `server.send(statusCode, contentType, content)` | 发送 HTTP 响应，200 表示成功，"text/html" 为 MIME 类型 |

#### 4. LittleFS 文件系统

考虑到可维护性和解耦性，选用 LittleFS 存储 HTML 等静态文件，通过 WebServer 进行读取传输。

**文件操作 API：**

| 函数 | 参数 | 说明 |
|-----|------|------|
| `LittleFS.open(path, mode)` | path: 文件路径；mode: r(读)/w(写覆盖)/a(追加) | 打开文件，返回 File 对象，失败时评估为 false |
| `server.streamFile(file, contentType)` | file: 已打开的 File 对象；contentType: 文件类型 | 将文件以数据流形式推送给浏览器，内存零压力 |
| `file.size()` | 无 | 获取文件大小（字节） |
| `file.readString()` | 无 | 将文件全部内容读取为字符串，适合小配置文件 |
| `file.read(buffer, length)` | buffer: 接收数组；length: 读取长度 | 读取二进制数据流 |
| `file.print(...)` | 同 Serial.print() | 写入文本内容到文件 |
| `file.close()` | 无 | 关闭文件指针，释放文件锁和内存缓冲区 |

**文件系统管理 API：**

| 函数 | 参数 | 说明 |
|-----|------|------|
| `LittleFS.begin(formatOnFail, basePath, maxOpenFiles)` | formatOnFail: 挂载失败是否格式化（建议 true） | 初始化并挂载 LittleFS，setup() 中最先执行 |
| `LittleFS.exists(path)` | path: 文件路径 | 检查文件是否存在 |
| `LittleFS.totalBytes()` | 无 | 返回分区总容量 |
| `LittleFS.usedBytes()` | 无 | 返回已用空间 |
| `LittleFS.format()` | 无 | 格式化整个分区 |
| `LittleFS.remove(path)` | path: 文件路径 | 删除指定文件 |

#### 5. 串口监视器输出丢失问题

串口监视器部分输出丢失，原因是 Serial 握手后未留足缓冲时间。

**解决：** 握手成功后添加 `delay(500)` 缓冲。

#### 6. WebServer 搭建与访问

成功通过 WebServer 库在开发板上创建简单的 Web 服务器，并通过电脑浏览器访问到开发板传输的 HTML 页面。

---

### 今日总结

- [x] 优化项目目录结构（src/main + src/lab）
- [x] 完成面包板首次测试，GPIO 控制 LED 闪烁
- [x] 解决串口监视器输出丢失问题
- [x] 成功搭建 WebServer 并通过浏览器访问

## Day 3

### 今日完成

#### 1. 正式项目架构（分层设计）

今天完成了从 lab 练习到正式项目的升级，搭建了 `src/main` + `include` 的项目结构（`.h` 放声明、`.cpp` 放实现）。

由于我此前有过后端学习的经历，在处理业务逻辑时，很自然地按照**分层解耦**的思想对架构进行了分离整理，将项目划分为以下四层：

| 层     | 类/文件               | 职责                                               |
| ------ | --------------------- | -------------------------------------------------- |
| 驱动层 | `IrrigationDriver`    | 单个引脚的 GPIO 开关封装（pinMode / digitalWrite） |
| 业务层 | `IrrigationService`   | 通道状态管理（开/关/查询/JSON 序列化）             |
| 控制层 | `WebServerController` | HTTP 路由注册、参数解析、错误码处理                |
| 应用层 | `main.cpp`            | 组装各层、初始化、WiFi 连接                        |

- 控制层通过依赖注入拿到业务层引用（`IrrigationService&`），不直接操作 GPIO；各层职责单一，便于替换和测试。

#### 2. 单通道 → 多通道升级

最开始是单个引脚控制一处，后决定将原本只控制单个引脚的灌溉系统，升级为支持多通道独立控制。

**为什么用 `std::vector` + `emplace_back`：**

- `new IrrigationDriver[count]` 要求类型有默认构造函数，且无法为每个元素传入不同的引脚参数；
- `emplace_back(pins[i])` 在容器内存上**原地构造**，参数直接传给构造函数，无需默认构造函数；
- vector 自动管理内存（RAII），无需手写 `new[]/delete[]`，避免内存泄漏。

**关键知识点：**

| 概念                    | 说明                                              |
| ----------------------- | ------------------------------------------------- |
| `std::vector`           | 动态数组，连续内存，自动扩容与释放                |
| `emplace_back(参数...)` | 在末尾原地构造元素，参数即构造函数的参数          |
| `reserve(count)`        | 提前预留容量，避免多次扩容搬移                    |
| `= delete`              | 禁用拷贝构造/赋值，防止对象被意外复制（单例语义） |
| 越界校验                | `isValidIndex()` 先判断索引再访问，避免数组越界   |

**接口变化：** 所有操作方法带 `size_t index`，越界返回 `false`；每个通道维护独立的 `isIrrigating` 状态，互不影响。

#### 3. API 设计（配合 docs/api.md）

 我先根据后端逻辑与任务需求设计出对应的 API（路由、参数、错误码），然后结合 AI 设计出合适的前端页面，前后端通过文档约定的接口对接。

**路由表：**

| 方法 | 路径                   | 参数             | 说明                      |
| ---- | ---------------------- | ---------------- | ------------------------- |
| GET  | `/irrigation`          | 无               | 返回控制页面 HTML         |
| GET  | `/irrigation/channels` | 无               | 返回通道列表 JSON 数组    |
| POST | `/irrigation/on`       | `channel=N`      | 开启指定通道              |
| POST | `/irrigation/off`      | `channel=N`      | 停止指定通道              |
| GET  | `/irrigation/status`   | 无 / `channel=N` | 全部通道数组 / 单通道对象 |

**错误码语义：**

| 状态码            | 含义           | 场景                     |
| ----------------- | -------------- | ------------------------ |
| `200 OK`          | 成功           | 操作完成                 |
| `400 Bad Request` | 参数缺失或非法 | 无 channel 参数 / 非数字 |
| `404 Not Found`   | 通道不存在     | channel 越界             |
| `409 Conflict`    | 状态冲突       | 重复开启 / 重复停止      |

**参数解析要点：** `server.arg("channel")` 取到的是字符串，`String::toInt()` 对非数字输入会静默返回 0，因此先逐字符 `isdigit` 校验，区分"参数非法（400）"与"通道越界（404）"。

---

### 踩坑记录

| 问题                                            | 原因                                                         | 解决方案                                                     |
| ----------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 烧录后页面还是旧 HTML                           | `uploadfs` 只更新文件系统；浏览器缓存旧页面                  | 改 HTML 后必须 `pio run -t uploadfs`；浏览器 Ctrl+F5 强刷    |
| `server.arg()` 编译报错"函数缺少 const 限定符"  | 所用 WebServer 库的 `arg()` 不是 const 方法                  | 去掉封装函数的 const 限定                                    |
| `?channel=abc` 被当成通道 0                     | `String::toInt()` 对非数字静默返回 0                         | 逐字符 `isdigit` 校验后再转换                                |
| 页面报 404 File Not Found                       | 代码里没有调用 `LittleFS.begin()`，文件系统未挂载，很烦人    | 在 `setup()` 中先调用 `LittleFS.begin(true)`（挂载失败自动格式化） |
| 请求页面/灌溉时设备反复崩溃重启，点击有概率失败 | 电脑 USB 口供电不足，WiFi 发射瞬间电流大导致电压跌落，协议栈 panic | 使用独立 5V 电源供电；已实测独立供电稳定                     |

### 今日总结

- [x] 完成四层架构的正式项目（main + include）
- [x] 单通道升级为多通道（Service / Controller / 前端）
- [x] 编写多通道 API 文档
- [x] 固件 + 文件系统烧录成功，接口实测全部通过

## Day 4

### 今日完成

#### 1. I2C 通信基础

**什么是 I2C：**

I2C（Inter-Integrated Circuit），也称 I²C 或 IIC，是一种广泛使用的两线制串行通信协议。

**I2C 特点：**

| 特点 | 说明 |
|-----|------|
| 两线通信 | 只需要 SDA（数据线）和 SCL（时钟线）两根信号线 |
| 主从架构 | 支持多个主设备和从设备在同一总线上 |
| 地址寻址 | 每个设备都有唯一的 7 位或 10 位地址 |
| 同步通信 | 通过时钟线进行同步，数据传输更可靠 |

**I2C 信号线：**

| 信号线 | 全称 | 说明 |
|-------|------|------|
| SDA | Serial Data Line | 串行数据线，用于传输数据 |
| SCL | Serial Clock Line | 串行时钟线，由主设备提供时钟信号，别名 SCK |

**I2C 初始化：**

| 函数 | 说明 |
|-----|------|
| `Wire.begin(int sda, int scl)` | 初始化 I2C 并指定 SDA 和 SCL 引脚 |
| `Wire.beginTransmission(address)` | 主设备尝试与指定地址的从设备建立通信 |
| `Wire.endTransmission()` | 结束通信尝试并返回状态码 |

**endTransmission 返回码：**

| 返回值 | 说明 |
|-------|------|
| 0 | 成功，从设备已应答（ACK） |
| 2 | 从设备在接收地址时未应答（NACK），最常见，表示该地址无设备 |
| 3 | 从设备在接收数据时未应答（NACK） |
| 4 | 其他错误 |

**I2C 设备地址：**

- 固定属性：I2C 地址是设备的硬件身份证（出厂烧录或引脚电平决定），非主控动态分配
- 主从机制：主设备通过呼叫特定地址与从设备通信，地址相同会发生硬件冲突

**I2C 扫描与开发流程：**

1. **调试阶段：** 运行 I2C 扫描程序（for 循环遍历 0x01~0x7F，`Wire.endTransmission()` 返回 0 表示发现设备），确认设备连接并获取硬件地址（如 0x3C）
2. **开发阶段：** 将获取的地址固化在正式代码中，直接向该地址收发数据

**扫描结果：** ✅ 成功扫描获得 I2C 模块地址：`0x3C`

#### 2. OLED 显示屏（SSD1306）

使用 Adafruit_SSD1306 库驱动 OLED 显示屏，实现文本显示。

**核心 API：**

| 函数 | 说明 |
|-----|------|
| `Adafruit_SSD1306 display(W, H, &Wire, RST)` | 创建显示对象，传入宽高、I2C 引脚、复位引脚 |
| `display.begin(SSD1306_SWITCHCAPVCC, 0x3C)` | 初始化显示屏，SSD1306_SWITCHCAPVCC 为供电模式，0x3C 为 I2C 地址 |
| `display.clearDisplay()` | 清空显示缓冲区 |
| `display.setRotation(n)` | 设置旋转角度（0/1/2/3），根据模组安装方向调整 |
| `display.setTextSize(n)` | 设置字体大小 |
| `display.setTextColor(color)` | 设置文字颜色，SSD1306_WHITE 为白，SSD1306_BLACK 为黑 |
| `display.setCursor(x, y)` | 设置光标位置 |
| `display.println(str)` | 写入文本并换行 |
| `display.display()` | 将缓冲区内容刷新到屏幕 |

**NAN 初始化技巧：**

将变量初始化为 `NAN`（Not a Number），可以表示"未赋值"或"无效值"状态，便于后续判断数据是否有效。

---

## Day 5

### 今日完成

#### 1. 温湿度传感器接入（DHT22）

今天接入的第一个新传感器是 DHT22（温湿度），它使用**单总线协议**，与我此前接触的 I2C（OLED）有本质区别：

**单总线 vs I2C：**

| 特性 | I2C（OLED） | 单总线（DHT22） |
|------|------------|----------------|
| 信号线 | SDA（数据）+ SCL（时钟）两根线 | 只有 DATA 一根线 |
| 时钟来源 | 主设备提供 SCL 时钟 | 无时钟线，靠**电平时序**编码 |
| 设备区分 | 靠 7 位**地址**（如 0x3C） | 不需要地址 |
| 通信方式 | 同步 | 靠拉高/拉低的**时长**表示 0/1 |

理解：I2C 像"同一条马路上的店铺，靠门牌号（地址）找到目标"；单总线像"电报员用特定节奏传递信息，不需要门牌号"。

**DHT22 关键参数：**

- 精度：±0.5°C / ±2%RH，分辨率 0.1
- **两次采样间隔必须 ≥ 2s**（DHT11 为 1s）——这是芯片协议要求

**lab 测试（`src/lab/dht_read_test.cpp`）：**

```cpp
DHT dht(47, DHT22);   // GPIO47, 型号 DHT22

void loop() {
    delay(2000);      // 满足 DHT22 采样间隔要求

    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {   // NAN 表示读取失败
        Serial.println("ERROR: failed to read DHT sensor!");
        return;
    }
    Serial.printf("Temperature: %.1f C | Humidity: %.1f %%\n", temperature, humidity);
}
```

**运行结果：** ✅ 成功

```
Temperature: 27.1 C | Humidity: 64.4 %
```

#### 2. 土壤传感器接入（HW-390）+ 标定

HW-390 是**电容式**土壤湿度传感器，属于**模拟量输出**（AO 引脚输出连续电压），与 I2C、单总线又是第三种类型：

| 类型 | 输出 | 读取方式 |
|------|------|---------|
| I2C（OLED） | 数字（地址寻址） | Wire 通信 |
| 单总线（DHT22） | 数字（时序编码） | 时序解析 |
| 模拟量（HW-390） | 连续电压 0~3.3V | ESP32 **ADC** 采样 |

**接线：** AO → GPIO2（ESP32-S3 的 ADC1 引脚），避开已占用的 GPIO1/4/8。

**关键点——ADC 标定：** 模拟量传感器没有统一标准值，每块板子都不一样，必须实测标定：

| 状态 | raw 值 | 电压 |
|------|--------|------|
| 悬空（干燥空气） | 3290 | 2.651V |
| 浸水（湿润） | 1057 | 0.852V |

- **方向：** 这块板子"越湿读数越低"（反向），不同批次可能相反，需实测确认
- **映射公式：** `湿度% = (3290 - raw) × 100 / (3290 - 1057)`，限幅 0~100
- 例：`raw = 2500` → `(3290-2500)/2233 ≈ 35%`

**抗抖动：** ADC 读数有噪声，`readRaw()` 连续采样 20 次取平均：

```cpp
int readSoilRaw() {
    long sum = 0;
    for (int i = 0; i < 20; ++i) {
        sum += analogRead(SOIL_PIN);   // GPIO2
        delay(5);
    }
    return (int)(sum / 20);
}
```

#### 3. 分层架构扩展（Driver / Service）

在 Day 3 的四层架构基础上，今天把新增的传感器模块纳入统一的命名与分类规范：

- **命名规范：** 属于 Driver 的加 `Driver` 后缀，Service 加 `Service`，Controller 加 `Controller`
- **目录分类：** `include/` 和 `src/main/` 下分别建立 `drivers/`、`services/`、`controllers/` 子目录

```
include/
├── drivers/         EnvSensorDriver / SoilSensorDriver / OledDisplayDriver / IrrigationDriver
├── services/        SensorService / IrrigationService
├── controllers/     WebServerController
├── common_config.h
└── wifi_app.h
```

**Driver 与 Service 的职责划分：**

| 层 | 回答的问题 | 职责 | 实例 |
|----|-----------|------|------|
| Driver | 硬件**怎么**操作 | 读原始数据、开关引脚、画屏；封装引脚/协议/标定 | `EnvSensorDriver` 知道 DHT 需 2s 间隔 |
| Service | 系统**何时**做、怎么做 | 调度采样节奏、聚合数据、驱动显示 | `SensorService` 决定每 2s 采样一轮 |
| Controller | 对外**怎么**暴露 | HTTP 路由、参数解析 | `WebServerController` |

**关于"节流"的两层含义**（易混）：

| 层次 | 节流目的 | 位置 |
|------|---------|------|
| DHT 2s 间隔 | 满足芯片**协议要求**（硬件细节） | `EnvSensorDriver` |
| 采样周期 2s | 系统**调度策略**（业务决策） | `SensorService` |

#### 4. OLED 显示封装

将 Day 4 的 OLED 测试代码封装为 `OledDisplayDriver`，加入两个关键优化：

**防闪烁 + 节流：**

```cpp
void OledDisplayDriver::drawIfChanged(const String& content, uint8_t textSize) {
    if (content == cachedContent) return;                    // 内容没变 → 不重绘
    if (now - lastDrawMs < DRAW_INTERVAL_MS) return;         // 最小绘制间隔(500ms)
    lastDrawMs = now;
    cachedContent = content;
    render(content, textSize);
}
```

**三排大字体显示：** 传感器页用 `textSize 2`，行距自适应字号，128x64 屏幕三行刚好排满：

```
T:28.9C      ← 温度
H:64.4%      ← 湿度
Soil:2%      ← 土壤
```

#### 5. Boot Loop 排障（本次最大收获）

**症状：** 烧录正式程序后，串口输出 `LittleFS mounted successfully`、`Connecting to SDK` 后设备无限复位重启（`rst:0x8 (TG1WDT_SYS_RST)`）。

**诊断过程：**

1. 先怀疑看门狗超时，加了 `esp_task_wdt_init(30)` 和喂狗——**无效**，说明不是看门狗本身的问题
2. 在 setup 中加**分步耗时打印 + `esp_reset_reason()`**，定位到：
   - `Reset reason: 5` = `ESP_RST_INT_WDT`（中断看门狗）
   - 崩溃点精确在 `WiFi.mode()` 之后
3. 结合 `PSRAM: 8386295`（板子实际有 8MB Octal PSRAM）推理出根因：

**根因：GPIO 与 PSRAM 冲突！**

```
platformio.ini: memory_type = qio_opi(Octal PSRAM)
        ↓
ESP32-S3 的 Octal PSRAM 数据线 = GPIO33~37
        ↓
OLED 初始化: Wire.begin(SDA=35, SCL=36)   ← 动了 PSRAM 数据线的引脚配置
        ↓
PSRAM 内存被破坏
        ↓
WiFi.mode() 访问到损坏内存 → 死锁 → 中断看门狗复位 → 无限重启
```

**修复：** OLED 的 SDA/SCL 从 GPIO35/36 换到 **GPIO9/10**（避开 PSRAM 占用的 GPIO33~37）。

**经验：** 复位码带 `WDT` 不一定是看门狗根因——WDT 只是"最后一刀"，真正原因是别处卡死；用 `esp_reset_reason()` + 分步打印定位崩溃点，比猜更快。

#### 6. WiFi 连接非阻塞化

**阻塞版**（旧）：`WiFi.begin()` 后 `while` 死等，最长卡 15 秒，期间其他功能全部停摆：

```cpp
while (WiFi.status() != WL_CONNECTED && millis() - start < timeout) {
    delay(500);
    Serial.print(".");
}
```

**非阻塞版**（新）：`WiFi.begin()` 立即返回，WiFi 在**后台自动连接**（ESP32 的 WiFi 是独立协处理模块），`loop()` 正常跑，用 `WiFi.status()` 轮询：

```cpp
bool connect_wifi_async(const char *ssid, const char *password) {
    WiFi.mode(WIFI_STA);
    WiFi.setTxPower(WIFI_POWER_11dBm);   // 降发射功率, 减少峰值电流
    WiFi.begin(ssid, password);          // 立即返回
    return true;
}

bool wifi_is_connected() { return WiFi.status() == WL_CONNECTED; }
```

- **好处：** 启动不卡顿、连不上也不阻塞其他功能、系统整体响应快
- 心跳输出每 10s 打印一次运行状态（WiFi 状态/温度/湿度/土壤/内存/IP），方便监控

#### 7. USB 供电问题

**现象：** 一插上板子电脑反复响起 USB 连接提示音（设备反复掉线重连），烧录时报 `ClearCommError failed`。

**原因：** WiFi 发射瞬间电流峰值大（约 400~500mA），USB 口供电不足 → 电压跌落 → USB 掉线。

**解决：**

| 方案 | 说明 |
|------|------|
| 换供电 | 手机充电头给板子供电（5V/1A+），USB 只走数据 |
| 主板后置 USB | 主板原生口供电比前置/Hub 强 |
| 软件降功率 | `WiFi.setTxPower(WIFI_POWER_11dBm)` 减小峰值电流（缓解） |

#### 8. Web API 扩展（/api/sensors）

在原有灌溉接口基础上，新增传感器数据接口：

**新增路由：**

| 方法 | 路径 | 返回 |
|------|------|------|
| GET | `/api/sensors` | `{"temperature":28.9,"humidity":64.4,"soil":2}` |

实现上通过**依赖注入**把 `SensorService` 传入 `WebServerController`，数据直接取 Service 周期采样缓存的 JSON。

**前端：** `irrigation.html` 顶部增加三张传感器卡片（🌡️温度 / 💧湿度 / 🪴土壤），JS 每 2s 轮询 `/api/sensors` 刷新：

```js
async function updateSensors() {
    let response = await fetch("/api/sensors");
    let data = await response.json();
    document.getElementById("temp").textContent = data.temperature.toFixed(1);
    ...
}
updateSensors();
setInterval(updateSensors, 2000);
```

**运行结果：** ✅ 接口与页面全部验证通过

```
GET /api/sensors → {"temperature":28.9,"humidity":64.4,"soil":2}
GET /irrigation/status → [{"gpioPin":1,"status":false},...]
```

---

### 踩坑记录

| 问题 | 原因 | 解决方案 |
|------|------|---------|
| 烧录正式程序后无限复位循环（`rst:0x8 TG1WDT_SYS_RST`） | OLED 用了 GPIO35/36，与 Octal PSRAM 占用的 GPIO33~37 冲突，`Wire.begin` 破坏 PSRAM 导致 WiFi 初始化崩溃 | OLED 改接 GPIO9/10（避开 PSRAM 区） |
| 复位码带 WDT 就以为是看门狗超时 | 看门狗只是"最后一刀"，真正根因是 PSRAM 损坏导致的死锁 | 用 `esp_reset_reason()` + 分步耗时打印定位崩溃点，别靠猜 |
| 头文件移入 `include/` 子目录后报 `No such file` | PlatformIO 不会递归搜索 include 子目录 | `build_flags` 加 `-Iinclude/drivers` 等 |
| `WebServer.h` 找不到（LDF 断链） | 框架库的 include 藏在 include 子目录头文件里，LDF 检测不到 | 在 src 的 `.cpp` 里显式 `#include <WebServer.h>` |
| 所有 lab 环境编译失败 | `common_config.h` include 了 `WebServerController.h`（引用 WebServer 库） | `common_config.h` 瘦身，`main.cpp` 显式 include 所需头文件 |
| 一插板子 USB 提示音反复响 / 烧录报 `ClearCommError failed` | WiFi 发射瞬间电流大，USB 口供电不足导致设备反复掉线 | 换充电头/主板后置 USB 供电；软件降 WiFi 功率缓解 |

### 今日总结

- [x] 接入 DHT22 温湿度传感器（单总线协议，2s 采样节流）
- [x] 接入 HW-390 土壤传感器（模拟量 ADC + 干/湿标定，3290/1057）
- [x] 新增 EnvSensorDriver / SoilSensorDriver / OledDisplayDriver / SensorService，扩展分层架构
- [x] include 分类目录重构（drivers / services / controllers）
- [x] OLED 三排大字体显示（防闪烁 + 节流刷新）
- [x] 定位并解决 boot loop（PSRAM 引脚冲突，OLED 改接 GPIO9/10）
- [x] connect_wifi 非阻塞化，降低 WiFi 发射功率
- [x] 解决 USB 供电不稳问题（充电头/主板后置 USB）
- [x] 新增 GET /api/sensors 接口 + 前端传感器卡片（2s 轮询）

## Day 6

### 今日完成

#### 1. MQTT 协议基础

MQTT（Message Queuing Telemetry Transport，消息队列遥测传输协议）是一种基于发布/订阅模式的轻量级物联网通信协议。

**MQTT 特点：**

| 特点 | 说明 |
|-----|------|
| 设计目标 | 低带宽、高延迟或不稳定网络、资源受限设备 |
| 通信模式 | 发布/订阅（Publish/Subscribe），异步传输 |
| 协议开销 | 固定头部最小仅 2 字节 |
| 连接方式 | 长连接 |

**MQTT vs HTTP：**

| 对比项 | MQTT | HTTP |
|-------|------|------|
| 模式 | 发布/订阅，异步 | 请求/响应，同步 |
| 开销 | 极小（2 字节头部） | 较大 |
| 适用场景 | IoT、低功耗设备 | Web 服务、REST API |

**核心架构：**

MQTT 设备之间不直接连接，全部通过 Broker 中转解耦。

| 组件 | 说明 |
|-----|------|
| 客户端（Client） | 发布消息的设备（Publisher）、接收消息的设备（Subscriber），或两者兼备 |
| 代理（Broker） | 消息调度中枢（如 EMQX、Mosquitto），负责接收、过滤并转发消息 |
| 主题（Topic） | 标识消息类别的层级字符串，如 `home/livingroom/temperature`，客户端通过订阅主题接收数据 |

**QoS 服务质量等级：**

| 等级 | 名称 | 说明 | 适用场景 |
|-----|------|------|---------|
| QoS 0 | 最多一次 | 消息发出去就不管，可能丢失 | 环境传感器数据（偶尔丢失影响不大） |
| QoS 1 | 至少一次 | 保证至少送到一次，可能重复 | 开关状态、报警提醒 |
| QoS 2 | 恰好一次 | 四次握手确保只送一次，无丢失无重复 | 金融计费、关键控制指令 |

**其他关键机制：**

| 机制 | 说明 |
|-----|------|
| 遗言消息（LWT） | 客户端连接时注册遗言，异常断开时 Broker 自动发送给订阅者，实现离线报警 |
| 保留消息（Retained） | Broker 持久保存某主题最新一条消息，新订阅者立即获取最新状态 |
| 心跳保活（Keep Alive） | 定期发送 PINGREQ/PINGRESP 报文保持长连接，超时则判定设备离线 |

**Topic vs Web 路由对比：**

| 对比项 | MQTT Topic | Web 路由 |
|-------|------------|----------|
| 模式 | 发布/订阅，一对多广播 | 请求/响应，一对一应答 |
| 数据流向 | Broker 中转，发布者不直接触达订阅者 | 客户端直连服务器 |
| 匹配方式 | 支持通配符（`+` 单层、`#` 多层） | 精确匹配 |
| 持久性 | 支持保留消息，新订阅者可获取最新状态 | 无状态，需自行实现 |
| 连接方式 | 长连接 | 短连接（HTTP） |

**Topic 通配符：**

| 通配符 | 说明 | 示例 |
|-------|------|------|
| `+` 单层通配符 | 匹配路径中的某一层 | `plant/+/temperature` 匹配 `plant/greenhouse1/temperature` 和 `plant/balcony/temperature` |
| `#` 多层通配符 | 匹配后面所有子层级，必须放在最后 | `plant/#` 匹配 `plant` 下所有消息（temp、soil/moisture、control/pump 等） |

**实践结果：** ✅ 成功

- 建立 EMQX Cloud 项目与 Broker
- MQTTX 客户端成功连接
- 通过订阅/发布成功传输与接收消息

**PubSubClient 库 API：**

| API | 作用 |
|-----|------|
| `PubSubClient client(wifiClient)` | 构造，绑定底层网络客户端 |
| `client.setServer(host, port)` | 设置 Broker 地址和端口 |
| `client.setCallback(函数)` | 注册"收到消息"的回调 |
| `client.connect(clientId, user, pass)` | 连接 Broker（带认证） |
| `client.connected()` | 是否还在线 |
| `client.publish(topic, payload)` | 发布消息 |
| `client.subscribe(topic)` | 订阅主题 |
| `client.loop()` | 必须频繁调用：保活 + 处理收到的消息 |

#### 2. 分层架构扩展：MqttDriver + MqttService

沿用 Day 3 的分层思想，MQTT 接入同样拆成 **Driver + Service 两层**，与 Irrigation 的划分一一对应：

| 层 | 类 | 回答的问题 | 职责 |
|----|-----|-----------|------|
| Driver | `MqttDriver` | MQTT 网络**怎么**收发 | 封装 TLS + PubSubClient，提供连接/发布/订阅/收消息回调，不含业务 |
| Service | `MqttService` | 云端通信**何时**做、怎么编排 | 断线重连、5s 周期上报、解析指令并控制灌溉 |

**依赖注入：** `MqttService` 构造时持有 `MqttDriver` / `SensorService` / `IrrigationService` 三个引用——数据从 `SensorService` 来，指令去 `IrrigationService` 执行，自己只做调度，不知道 GPIO 和网络细节。

**`MqttService.update()` 的编排逻辑：**

```
未连接 → 每 3s 重试 connect()(节流), 成功后订阅控制主题(只做一次)
已连接 → mqtt.loop() 保活收信; 每 5s publishData() 上报一次
```

#### 3. 关键技术点

**TLS 加密连接：** EMQX Cloud Serverless 只开放 TLS 端口 `8883`，必须用 `WiFiClientSecure` 并调用 `setInsecure()`（跳过证书校验，演示用；正规做法是下载 CA 证书用 `setCACert()`）。

**静态回调 + 单例指针（最绕的地方）：**

- PubSubClient 要求回调必须是**静态函数**——成员函数隐含 `this` 参数，库无法调用
- 静态函数没有 `this`，访问不了成员变量 → 用**单例指针** `instance` 记录对象地址
- 完整消息链：`库 → onMessage(静态) → instance->userCallback → 业务处理`

**两层 setCallback 的"接力"：**

| 环节 | 谁注册 | 注册谁 | 作用 |
|------|--------|--------|------|
| 第一棒 | `PubSubClient::setCallback` | `onMessage`（静态） | 库收到消息 → 通知 Driver |
| 第二棒 | `MqttDriver::setCallback` | Service 的桥接函数 | Driver 收到 → 转给业务 |

Driver 只提供"注册口子"，不知道业务，保持纯粹。

**回调 vs 轮询的设计取舍：**

| 数据类型 | 例子 | 特点 | 正确模式 |
|---------|------|------|---------|
| 事件型 | 控制指令 `{"pump":"on"}` | 每条都要执行、不能丢 | **回调（推）** |
| 状态型 | 传感器数值 | 只要最新值，旧值丢了无所谓 | **缓存 + 读取（拉）** |

本项目两种模式都有：`getSensorsJson()` 是"拉"（Service 读缓存），`onCommand` 是"推"（消息到达立即处理）。

#### 4. JSON 数据格式设计

**上报（设备 → 云端，每 5s）：**

```json
{"device":"esp32-s3","temperature":28.9,"humidity":64.4,"soil":2}
```

**下发（云端 → 设备）：**

```json
{"pump":"on","index":0}    // 打开通道 0
{"pump":"off","index":2}   // 关闭通道 2
```

**多通道设计：** 指令携带 `index` 字段指定灌溉通道，配合 `IrrigationService` 的多通道并行控制；`index` 缺省时默认通道 0。

**解析方式：** 用字符串 `indexOf` 判断（pump 字段、index 字段），不引入 JSON 库，与项目手动拼 JSON 的风格保持一致。

#### 5. 真机验证

**数据上报：** MQTTX 订阅 `garden/esp32-s3/data` → 每 5 秒收到一条传感器 JSON。

**指令下发：** MQTTX 发布 `{"pump":"on","index":0}` 到 `garden/esp32-s3/cmd` → 串口打印 `pump ON -> channel 0`，对应通道 LED 点亮。

**运行结果：** ✅ 成功，双向通信全部验证通过

---

### 踩坑记录

| 问题 | 原因 | 解决方案 |
|------|------|---------|
| `isConnected()` 编译报 `discards qualifiers` | `PubSubClient::connected()` 不是 const 方法，封装标了 const 导致类型不匹配 | 去掉 const 限定符（库方法的 const 属性决定封装能否标 const） |

### 今日总结

- [x] 学习 MQTT 协议（发布/订阅、Topic 通配符、QoS、Will/Retain、KeepAlive）
- [x] 搭建 EMQX Cloud Serverless 部署，MQTTX 连接并手动收发验证
- [x] 新增 MqttDriver（TLS + PubSubClient 封装，静态回调 + 单例指针转发）
- [x] 新增 MqttService（重连节流 / 5s 周期上报 / 指令解析控制多通道）
- [x] 理解回调 vs 轮询的设计取舍（事件型用推、状态型用拉）
- [x] JSON 格式设计（上报字段 + 下发带 index 多通道控制）
- [x] 真机验证：数据上报 + 云端指令控制指定通道

## Day 7

### 今日完成

#### 1. FreeRTOS 阻塞队列

队列（Queue）是 FreeRTOS 中任务间通信的核心机制，支持阻塞式读写。

**核心 API：**

| 函数 | 说明 |
|-----|------|
| `xQueueCreate(length, itemSize)` | 创建队列，length 为队列长度，itemSize 为每个元素大小 |
| `xQueueSend(queue, item, timeout)` | 向队列发送数据，队列满时阻塞等待（直到超时） |
| `xQueueSendToFront(queue, item, timeout)` | 发送到队列头部 |
| `xQueueSendToBack(queue, item, timeout)` | 发送到队列尾部（默认） |
| `xQueueReceive(queue, buffer, timeout)` | 从队列读取数据，队列空时阻塞等待（直到超时） |
| `xQueuePeek(queue, buffer, timeout)` | 查看队列头部数据但不移除 |
| `uxQueueMessagesWaiting(queue)` | 获取队列中当前消息数量 |

**阻塞机制：**

- **发送阻塞：** 队列满时，发送任务阻塞，直到有空间或超时
- **接收阻塞：** 队列空时，接收任务阻塞，直到有数据或超时
- `timeout = portMAX_DELAY` 表示永久阻塞，`timeout = 0` 表示非阻塞

**任务抢占机制：**

FreeRTOS 是抢占式调度器，高优先级任务就绪时会立即抢占低优先级任务。

| 概念 | 说明 |
|-----|------|
| 优先级 | 任务创建时指定，数字越大优先级越高 |
| 抢占 | 高优先级任务就绪 → 低优先级任务被挂起，高优先级立即执行 |
| 时间片 | 同优先级任务通过时间片轮转调度 |

**队列句柄：**

创建队列后返回一个句柄（`QueueHandle_t`），后续所有操作都通过这个句柄访问队列。

```c
QueueHandle_t xQueue = xQueueCreate(10, sizeof(int));  // 创建并获取句柄
xQueueSend(xQueue, &data, 0);  // 通过句柄操作
```

**xQueueOverwrite vs xQueueSend：**

| 函数 | 适用场景 | 行为 | 示例 |
|-----|---------|------|------|
| `xQueueOverwrite` | 传感器数据等只需要最新值 | 队列满时覆盖旧数据，始终只保留最新一条 | 温度/湿度读数 |
| `xQueueSend` | 消息流、事件队列 | 队列满时阻塞等待或失败，保留所有消息 | 控制指令、日志 |

**阻塞参数详解：**

| timeout 值 | 行为 | 适用场景 |
|-----------|------|---------|
| `0` | 非阻塞，立即返回 | 快速检查队列是否有数据 |
| `pdMS_TO_TICKS(ms)` | 阻塞最多 ms 毫秒 | 等待数据但不想永久卡死 |
| `portMAX_DELAY` | 永久阻塞直到有数据 | 任务只负责处理队列数据，无其他工作 |

**任务创建与运行：**

| 函数 | 说明 |
|-----|------|
| `xTaskCreate(func, name, stackSize, params, priority, &taskHandle)` | 创建任务 |
| `xTaskCreatePinnedToCore(func, name, stackSize, params, priority, &taskHandle, coreID)` | 创建任务并绑定到指定 CPU 核心（ESP32 双核：0 或 1） |

**xTaskCreatePinnedToCore 参数详解：**

| 参数 | 类型 | 说明 | 示例 |
|-----|------|------|------|
| `pvTaskCode` | 函数指针 | 任务入口函数（不要加括号） | `oledTask` |
| `pcName` | 字符串 | 任务名称，仅调试用，最多 16 字符 | `"oled"` |
| `usStackDepth` | uint32_t | 栈空间大小（字节），填小了会栈溢出重启 | `2048` 或 `4096` |
| `pvParameters` | void* | 传递给任务函数的参数，不需要则填 NULL | `&oledDisplay` |
| `uxPriority` | UBaseType_t | 优先级（数字越大越高，0 最低） | `1` ~ `5` |
| `pvCreatedTask` | TaskHandle_t* | 任务句柄输出指针，用于后续操作该任务；不需要则填 NULL | `NULL` |
| `xCoreID` | BaseType_t | 绑定的 CPU 核心 ID | `0`(PRO), `1`(APP), `tskNO_AFFINITY`(自动) |

**ESP32 双核说明：**

| 核心 | 名称 | 通常用途 |
|-----|------|---------|
| Core 0 | PRO_CPU | Wi-Fi/蓝牙协议栈 |
| Core 1 | APP_CPU | 用户主逻辑、UI、传感器 |
| `vTaskDelete(taskHandle)` | 删除任务（传 NULL 删除自身） |
| `vTaskDelay(ms)` | 任务延时，让出 CPU 给其他任务执行 |
| `vTaskSuspend(taskHandle)` | 挂起任务 |
| `vTaskResume(taskHandle)` | 恢复任务 |

**队列通信模式：**

```
Task A (生产者)  →  xQueueSend()  →  [Queue]  →  xQueueReceive()  →  Task B (消费者)
```

- **一对一：** 一个队列连接两个任务
- **多对一：** 多个生产者向同一队列发送，一个消费者接收
- **一对多：** 一个生产者，多个消费者（需要配合其他机制区分）

#### 2. 任务化架构设计

把原来的"单循环轮询"（`loop()` 里依次调用各 `update()`）改造成 **FreeRTOS 多任务**，任务划分如下：

| 任务 | 核 | 优先级 | 周期/触发 | 职责 |
|------|----|--------|----------|------|
| `sensorTask` | 0 | 2 | 2000ms 周期 | 采样传感器，打包 `SensorData_t`，分发队列 |
| `mqttTask` | 0 | 2 | 20ms 循环 / 5000ms 上报 | MQTT 连接、保活、收指令、周期上报 |
| `controlTask` | 1 | **3(最高)** | 事件驱动(队列集) | 手动指令执行 + 自动灌溉（唯一执行者） |
| `oledTask` | 1 | 1 | 事件驱动(队列) | 收数据刷新 OLED |
| `loopTask(Web)` | 0 | 1 | HTTP 异步 | Web 服务器（Arduino 主循环） |

**TaskConfig.h 公共中枢**：集中定义任务参数宏、跨任务数据结构、队列句柄声明：

```cpp
// 跨任务数据结构
typedef struct {
    float    temperature;   // °C
    float    humidity;      // %
    int      soilPercent;   // 0~100
    uint32_t timestamp;
} SensorData_t;

typedef struct {
    uint8_t index;    // 通道索引
    bool    pumpOn;   // true=开泵
    int8_t  mode;     // -1=不切换, 0=自动, 1=手动
} Command_t;

// 队列句柄声明(extern), 由 main.cpp 定义
extern QueueHandle_t oledQueue;
extern QueueHandle_t latestDataQueue;
extern QueueHandle_t autoIrrQueue;
extern QueueHandle_t manualIrrQueue;
```

**任务参数传递**：任务函数签名固定 `void task(void* param)`，通过 `void*` 传任意数据，任务内用 `static_cast` 还原：

```cpp
// main.cpp 创建任务时把对象地址传进去
xTaskCreatePinnedToCore(sensorTask, "sensor", 4096, &sensorTaskParams, 2, NULL, 0);

// 任务内还原
SensorTaskParams* params = static_cast<SensorTaskParams*>(param);
```

#### 3. 队列通信设计

**单消费者陷阱（重要认知）：** FreeRTOS 队列是**单消费者**——一条数据只能被一个任务取走。若让两个任务消费同一队列，会竞争取数据、互相饿死。**解法：每消费者独立队列。**

**状态型 vs 事件型（overwrite vs send）：**

| 队列 | 数据类型 | 模式 | 原因 |
|------|---------|------|------|
| `oledQueue`(容量1) | 状态(最新值) | `xQueueOverwrite` | OLED 只显示最新 |
| `latestDataQueue`(容量1) | 状态(最新值) | `xQueueOverwrite` + `xQueuePeek` | MQTT 只读最新，不消费 |
| `autoIrrQueue`(容量1) | 状态(变化才发) | `xQueueSend` | 自动灌溉指令，状态变化才发 |
| `manualIrrQueue`(容量5) | **事件(每条都要)** | `xQueueSend` | 控制指令不能丢！ |

**单位置队列 + overwrite/peek（"公告板"模型）：**

```cpp
// sensorTask 发布最新值(覆盖旧值, 永远只留最新)
xQueueOverwrite(latestDataQueue, &data);

// mqttTask 偷看(不删除, 公告板内容保留)
SensorData_t latest;
xQueuePeek(latestDataQueue, &latest, 0);
```

- `xQueueOverwrite`：容量必须为 1，覆盖旧数据
- `xQueuePeek`：读副本**不消费**，公告板永远保留最新一条，多个读者都能读到

**队列集（QueueSet）：一个任务等多个队列**

`controlTask` 要同时等"手动指令"和"自动灌溉"两个队列，用队列集：

```cpp
QueueSetHandle_t set = xQueueCreateSet(6);          // 容量 = 各队列容量之和
xQueueAddToSet(manualIrrQueue, set);
xQueueAddToSet(autoIrrQueue, set);

QueueSetMemberHandle_t ready = xQueueSelectFromSet(set, portMAX_DELAY);  // 阻塞等任一
if (ready == manualIrrQueue) { /* 手动指令 */ }
else if (ready == autoIrrQueue) { /* 自动灌溉 */ }
```

队列集让任务**真正事件驱动**——任何一个队列有数据就唤醒，没数据就睡觉。

#### 4. 控制收敛与模式状态机

**控制收敛（唯一执行者）：** Web / MQTT / 自动灌溉三路控制指令**统一汇聚到 `manualIrrQueue` / `autoIrrQueue`**，只有 `controlTask` 真正调用 `IrrigationService`——控制动作天然串行，无并发竞争。

```
MQTT 指令 ──► mqttTask ──► manualIrrQueue ─┐
Web 指令 ──► WebServerController ──► manualIrrQueue ─┼──► controlTask ──► IrrigationService
自动灌溉 ──► sensorTask 判断 ──► autoIrrQueue ──┘
```

**模式状态机（AUTO / MANUAL）：**

| 指令 | 效果 |
|------|------|
| `{"pump":"on"/"off","index":N}` | 执行开关 + **自动切 MANUAL** |
| `{"mode":"auto"}` | 切自动模式（土壤低于阈值自动开泵） |
| `{"mode":"manual"}` | 切手动模式（自动灌溉停止判断） |

- 开机默认 **AUTO**；任何手动 pump 指令隐含"我要手动控制"→ 自动切 MANUAL
- 回 AUTO 需显式发 `{"mode":"auto"}`（避免自动灌溉"插一脚"）
- 模式状态上报：MQTT JSON 加 `"mode":"auto"/"manual"` 字段；Web `/api/sensors` 同步返回

#### 5. 自动灌溉优化

**改进点：** 阈值判断从 controlTask 移到 **sensorTask（数据生产方）**，且**状态变化才发指令**：

```cpp
// sensorTask 内:
bool wantPump = autoPumpState;                       // 默认保持
if (data.soilPercent < AUTO_IRR_DRY_THRESHOLD)  wantPump = true;    // 干燥 → 开
else if (data.soilPercent > AUTO_IRR_WET_THRESHOLD) wantPump = false; // 湿润 → 关

if (wantPump != autoPumpState) {                     // ★ 状态变化才发指令
    autoPumpState = wantPump;
    xQueueSend(autoIrrQueue, &cmd, 0);               // 才唤醒 controlTask
}
```

- **消除冗余**：土壤湿度没跨阈值时，controlTask 完全不被唤醒
- **双阈值防抖**：< 30% 开泵、> 60% 关泵，中间区间保持现状（防止在阈值附近抖动导致反复开关）
- **状态同步**：`autoPumpState` 初始化为**实际泵状态**，切回 AUTO 时重置（避免与真实状态脱节）

#### 6. SensorService 数据打包

**改进点：** 数据打包逻辑从任务层收敛到 **Service 层**（数据所有者），任务一行调用：

```cpp
// SensorService 新增:
SensorData_t getData() const {          // 短临界区打包, 防混合快照
    static portMUX_TYPE criticalMux = portMUX_INITIALIZER_UNLOCKED;
    SensorData_t data;
    portENTER_CRITICAL(&criticalMux);   // 三个字段连续读, 不被写打断
    data.temperature = env.getTemperature();
    data.humidity    = env.getHumidity();
    data.soilPercent = soil.getMoisturePercent();
    portEXIT_CRITICAL(&criticalMux);
    data.timestamp = millis();
    return data;
}

SensorData_t updateAndGet() { update(); return getData(); }   // 采样+打包一步

// sensorTask 里一行搞定:
SensorData_t data = sensors->updateAndGet();
```

- **职责归属**：数据格式的定义和组装属于 Service，任务层不该知道内部字段
- **一致性**：短临界区保证三个字段来自同一次读取（避免"混合快照"）
- **复用**：`getSensorsJson()` 内部也复用 `getData()`（Web 查询一致性同步提升）

#### 7. 并发安全基础

**原子性（什么会被打断）：**

| 操作 | 原子吗 | 例子 |
|------|--------|------|
| 单条 CPU 指令 | ✅ 原子 | 32 位 MCU 读写一个 int/float |
| 队列/信号量操作 | ✅ 原子 | `xQueueSend`（内核临界区保护） |
| 临界区内代码 | ✅ 原子 | `portENTER_CRITICAL` 包裹的多条语句 |
| 多条指令组合 | ❌ 可打断 | `i++`（读-改-写三步） |
| 多字段分开读 | ❌ 可打断 | 三次 getter 分别调用 |

**临界区（双核需 spinlock）：** ESP32 是双核，老式无参 `portENTER_CRITICAL()` 只关当前核中断，另一个核仍可访问共享内存 → 必须用带 `portMUX_TYPE` 自旋锁的版本，保证"同一时刻只有一个核在临界区"。

**共享 vs 队列（"不碰共享"）：**
- **队列** = 值拷贝（快递）：数据复制一份给你，天然无竞争，无需保护
- **共享变量** = 公告栏（多人读写同一块内存）：需要 volatile / 临界区保护
- 设计目标：**能用队列的走队列**（值拷贝），共享变量越少越好

### 踩坑记录

| 问题 | 原因 | 解决方案 |
|------|------|---------|
| 链接报 `undefined reference to 'oledQueue'` | TaskConfig.h 里 `extern` 只声明，main.cpp 只定义了 1 个队列句柄，其他被引用却没定义 | 所有 extern 声明的句柄都要在 main.cpp 定义（分配内存） |
| `portENTER_CRITICAL()` 编译报"too few arguments" | ESP32(IDF v4.4+) 的临界区 API 需要显式 `portMUX_TYPE*` 参数 | 定义 `static portMUX_TYPE mux` + `portENTER_CRITICAL(&mux)` |
| 误以为队列可以"广播"给多个消费者 | FreeRTOS 队列是单消费者，一条数据只能被一个任务取走 | 每消费者独立队列；只读最新值的用单位置队列 + peek |
| 任务优先级文档与实际不符 | 前期 HTML 文档按旧设计写的优先级 | 统一以 TaskConfig.h 宏为准，文档同步修正 |
| `getData()` 想用无参临界区 | 记混了旧版 API | ESP32 双核必须带 spinlock 参数 |

### 设计改进（中途演进）

| 改进 | 内容 | 动因 |
|------|------|------|
| 读缓存 → 单位置队列 | mqttTask 从"读 SensorService 缓存"改为"单位置队列 overwrite/peek" | 避免共享变量 + 保证结构体一致性 |
| `controlQueue` → `autoIrrQueue` | 队列职责命名明确（只管自动灌溉） | 手动指令走 manualIrrQueue，职责分离 |
| 自动灌溉判断下沉 | 阈值判断从 controlTask 移到 sensorTask | 数据生产方判断 + 状态变化才发，消除冗余唤醒 |
| 数据打包收敛到 Service | 新增 `getData()` / `updateAndGet()` | 格式定义属于数据所有者，任务一行调用 |
| 状态跟踪从实际起步 | `autoPumpState` 初始化为实际泵状态，切回 AUTO 重置 | 避免与真实状态脱节 |
| 手动/自动模式切换 | 新增模式状态机 + 模式上报 MQTT/Web | 手动控制与自动灌溉互斥，行为可预测 |

### 今日总结

- [x] 学习 FreeRTOS 队列/阻塞/抢占/双核/任务创建（Day 7 第 1 节）
- [x] 完成项目任务化改造（sensor / oled / control / mqtt / web 五任务）
- [x] 掌握队列通信设计（独立队列、overwrite/peek、队列集）
- [x] 理解控制收敛（唯一执行者）与 AUTO/MANUAL 模式状态机
- [x] 优化自动灌溉（阈值判断下沉 + 状态变化才发 + 双阈值防抖）
- [x] 数据打包收敛到 Service（getData/updateAndGet + 短临界区）
- [x] 理解并发安全（原子性、临界区、共享 vs 队列）
- [x] 两个页面（HTTP/MQTT）添加模式切换功能

## Day 8

### 今日完成

#### 1. MQTT 保留消息重放问题（状态显示修复）

**现象：** 设备每次重启/重连 Broker 后，0 号灌溉泵"自己"打开，且模式显示为手动。

**排查思路：** 先排除显示问题（重新加载页面、切换模式都无效）→ 怀疑有旧指令在重放 → 顺着 MQTT 机制找到根因。

**根因：Retain 保留消息。** 之前测试时用 retain 标志发过 `{"pump":"on"}`，Broker 会持久保存该主题的**最后一条保留消息**；设备重连并重新订阅 `garden/esp32-s3/cmd` 后，Broker 立刻把这条旧指令重放给设备——于是启动即开泵、自动切手动。

**Retain 机制：**

| 概念 | 说明 |
|-----|------|
| 保留消息（Retained） | 发布时带 retain 标志，Broker 持久保存该主题最新一条 |
| 重放时机 | 新订阅者 / 重连的设备订阅时，立刻收到这条保留消息 |
| 适用场景 | 状态类数据（如"灯当前是开的"），新订阅者上线即可拿到最新状态 |
| 隐患 | 控制类指令（一次性事件）被重放 = 意外执行旧命令 |

**修复：** 连接成功后，向控制主题发布**空 payload + retain**——空消息即"清除保留消息"：

```cpp
mqttDriver.subscribe(topicCmd);
mqttDriver.publish(topicCmd, "", true);   // 空 payload + retain = 清除旧保留消息
```

**PubSubClient 的 publish 重载：**

| 函数 | 说明 |
|-----|------|
| `publish(topic, payload)` | 普通发布，Broker 不保存 |
| `publish(topic, payload, retained)` | retained=true 表示保留；payload 传空串 = 清除该主题的保留消息 |

**经验：** 环境数据适合 retain（新订阅者拿到最新值），控制指令**不应该** retain；历史残留用空消息清除。

#### 2. 控制收敛补全 + 状态回传

**控制收敛补全：** Day 7 建立了"唯一执行者"模型（MQTT 指令 → manualIrrQueue → controlTask），但 Web 页面的 `/irrigation/on`、`/irrigation/off` 还停留在旧实现——直接调用 IrrigationService，绕过了队列，形成**第二个执行者**。今天把 Web 指令也改为发送 manualIrrQueue：

```
MQTT 指令 ──► mqttTask ──► manualIrrQueue ─┐
Web 指令 ──► WebServerController ──► manualIrrQueue ─┼──► controlTask ──► IrrigationService
自动灌溉 ──► sensorTask 判断 ──► autoIrrQueue ──┘
```

三路入口全部收敛，控制动作天然串行，无并发竞争。

**状态回传（mode + channels）：** 上报 JSON 加入模式字段与各通道**真实**开关状态，页面/云端直接读取真值，不再自行猜测：

```json
{"device":"esp32-s3","temperature":28.9,"humidity":64.4,"soil":30,
 "mode":"auto","channels":[{"index":0,"status":false},{"index":1,"status":false}]}
```

| 字段 | 说明 |
|------|------|
| `mode` | 当前模式 auto/manual，直接读取 `volatile controlMode` |
| `channels` | 各通道真实状态数组，逐通道查询 `isIrrigating(i)` |

#### 3. 配置持久化：ConfigService

**需求：** WiFi/MQTT 账号、灌溉阈值、默认模式全部硬编码在代码里，改配置必须改代码重新编译烧录。今天引入 ConfigService，把配置存到 LittleFS 的 `/config.json`：启动时读取、Web 可改可存、重启不丢。

**LittleFS 配置读写：**

| 函数 | 说明 |
|-----|------|
| `LittleFS.exists(path)` | 文件是否存在；不存在则保留默认值，不创建 |
| `LittleFS.open(path, "r"/"w")` | 打开文件读/写，返回 File 对象 |
| `file.readString()` | 整文件读为 String（小配置文件足够） |
| `file.print(content)` | 写入文本内容 |
| `file.close()` | 必须关闭（释放文件锁与缓冲区） |

**手动 JSON 解析（不引库）：** 配置是扁平 JSON，用字符串搜索实现三个工具函数：

| 函数 | 作用 |
|------|------|
| `getField(json, key)` | 提取 `"key":value` 原始值（字符串去引号、数字原样返回）；找不到返回空串 |
| `getStringField(json, key, def)` | 字符串字段，为空则用默认值 |
| `getIntField(json, key, def)` | 数字字段，为空则用默认值 |

实现思路：`indexOf` 定位 `"key"` → 找冒号 → 跳过空格 → 字符串取引号内内容、数字取到逗号或右括号。

**为什么不用 ArduinoJson 库：** 配置只有 9 个扁平字段，手动解析约 30 行；引入库会显著增加固件体积（Flash/RAM），对简单场景不划算。

**增量更新（updateFromJson）：** Web 提交的 JSON 只更新**存在**的字段，缺省字段保持原值——避免整包覆盖把没提交的配置清掉：

```cpp
if (getField(json, "dryThreshold") != "") dryThreshold = getIntField(json, "dryThreshold", dryThreshold);
```

**编译期宏 vs 运行期变量：**

| 方式 | 修改阈值 | 特点 |
|------|---------|------|
| 编译期宏 `#define` | 改代码 → 重编译 → 重烧录 | 简单，但改配置成本高 |
| 运行期变量（ConfigService 读文件） | Web 页面直接改、保存 | 配置与代码分离，运行时生效 |

阈值因此从宏改为 `extern volatile int autoIrrDryThreshold / autoIrrWetThreshold`，main.cpp 启动时从 ConfigService 赋值；sensorTask 每次判断前读取。跨任务共享、读多写少，volatile 足够。

**Web 接口：**

| 方法 | 路径 | 说明 |
|------|------|------|
| GET | `/api/config` | 返回当前配置 JSON |
| POST | `/api/config` | 提交配置（增量更新）并保存到文件 |

#### 4. OTA 远程更新

**问题：** 固件迭代要插 USB 重新烧录，设备部署在室外不现实。OTA（Over-The-Air）让固件通过 WiFi 上传更新。

**A/B 双分区原理：** ESP32-S3 的 Flash 里有**两份固件分区**，配合元数据分区实现"升级失败自动回滚"：

| 分区 | 作用 |
|------|------|
| `app0` | 当前运行固件 |
| `app1` | 另一份固件（新固件写入这里） |
| `otadata` | 记录"哪份是有效固件"，启动时按它选择 |

流程：新固件写入**非运行**分区 → 校验通过后更新 otadata → 重启切到新固件；若新固件启动失败，otadata 未提交成功则自动回滚旧固件——**升级失败不会变砖**。

**Update 库 API：**

| 函数 | 说明 |
|-----|------|
| `Update.begin(size)` | 开始 OTA；size 用 `UPDATE_SIZE_UNKNOWN` 表示未知（Web 流式） |
| `Update.write(buf, len)` | 写入一块固件数据（分块接收） |
| `Update.end(true)` | 结束并校验，通过才提交分区切换 |
| `Update.abort()` | 中止（如密钥错误） |
| `Update.hasError()` | 是否发生错误 |
| `Update.printError(Serial)` | 打印错误信息 |

**WebServer 流式上传：** `server.on("/update", HTTP_POST, ...)` 注册两个回调（接收完成 + 分块接收），三阶段写入：

| 阶段 | 处理 |
|------|------|
| 开始 `UPLOAD_FILE_START` | 校验密钥（`?key=`），`Update.begin()` |
| 传输 `UPLOAD_FILE_WRITE` | `Update.write()` 逐块写入 |
| 结束 `UPLOAD_FILE_END` | `Update.end(true)` 校验 → `ESP.restart()` |

**密钥校验：** 页面提交时把密码拼到 URL `?key=xxx`，服务端用 `server.arg("key")` 与 `OTA_KEY` 比对，错误立即 `Update.abort()`——防止任意人刷固件。

**设计决策——OTA 页面为何内嵌：** OTA 页面若存成文件（LittleFS），万一文件系统损坏、配置被清，设备既连不上网也没有上传入口——**救砖通道失效**。把 OTA 页内嵌在固件里，只要固件能跑，更新通道就在。

#### 5. 历史数据：HistoryService

**需求：** 传感器只有当前值，看不到变化趋势。HistoryService 用**环形缓冲区**保存最近 N 条采样，Web 接口输出时间序列。

**环形缓冲区（Ring Buffer）：** 固定数组 + 下标实现"存满自动覆盖最旧"，内存开销固定、无动态分配：

| 成员 | 作用 |
|------|------|
| `buffer[MAX_POINTS]` | 固定数组（2000 条 × 16B ≈ 32KB RAM） |
| `head` | 下一个写入位置 |
| `count` | 当前有效条数（满后不再增长，覆盖最旧） |
| `lastAddMs` | 降频节流时间戳 |

写入与读取都用**取模索引**，写满后从最旧开始覆盖：

```cpp
buffer[head] = data;
head = (head + 1) % MAX_POINTS;             // 到头回绕
if (count < MAX_POINTS) count++;

// 读取: 最旧元素位置 = (head + MAX_POINTS - count) % MAX_POINTS
```

**存储节奏：** 采样 2s 一条，存储间隔也设为 2s（与正常采样同步），2000 条 ≈ 66 分钟；节流代码保留，防止将来采样频率提高时数据爆炸。

| 项 | 值 |
|----|-----|
| 存储间隔 | 2s（与采样同步） |
| 容量 | 2000 条 ≈ 66 分钟 |
| 输出 | `[{"ts":..,"t":28.90,"h":64.40,"s":30},...]`（2 位小数） |

**接口：** `GET /api/history?limit=N`，`toJson(limit)` 从最旧到最新输出，limit 限制条数防止一次传输过多。

**局限（后续改进）：** 数据在内存，重启即丢失；后续可考虑写入文件持久化。

---

### 踩坑记录

| 问题 | 原因 | 解决方案 |
|------|------|---------|
| 启动即开泵 + 模式显示手动 | Broker retain 重放了之前测试用的 `{"pump":"on"}` | 连接成功后 `publish(topicCmd, "", true)` 清除保留消息 |
| 改阈值必须重新编译烧录 | 阈值是编译期宏，写死在代码里 | 改为运行期变量 + ConfigService 文件持久化 |

### 设计改进（中途演进）

| 改进 | 内容 | 动因 |
|------|------|------|
| 控制收敛补全 | Web on/off 也走 manualIrrQueue | 消除绕过 controlTask 的第二执行者 |
| 状态回传 | 上报 JSON 含 mode + channels 真实状态 | 页面/云端读真值，不自行猜测 |
| 配置持久化 | ConfigService + /config.json | 配置与代码分离，运行时修改 |
| 增量更新 | updateFromJson 缺省字段保持原值 | 避免整包覆盖丢配置 |
| OTA 页面内嵌 | 页面存固件而非文件系统 | 文件系统损坏时仍有救砖通道 |
| 历史采样同步 | 存储间隔 2s 与采样对齐 + 精度 2 位小数 | 曲线更密更平滑 |

### 今日总结

- [x] 定位并修复 MQTT retain 重放问题（启动即开泵）
- [x] Web 指令收敛到 manualIrrQueue（唯一执行者闭环）
- [x] MQTT 上报加入 mode + channels 状态
- [x] ConfigService 配置持久化（LittleFS /config.json + 手动 JSON 解析）
- [x] OTA 远程更新（A/B 双分区 + Update 库 + 密钥校验 + 内嵌救砖页）
- [x] HistoryService 历史数据（环形缓冲 + 2s 同步采样）
- [x] 新增 /api/config、/api/history 接口
