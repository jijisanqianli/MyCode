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

---

## Day 3

### 今日完成

#### 1. 正式项目架构（分层设计）

今天完成了从 lab 练习到正式项目的升级，搭建了 `src/main` + `include` 的项目结构（`.h` 放声明、`.cpp` 放实现）。

由于我此前有过后端学习的经历，在处理业务逻辑时，很自然地按照**分层解耦**的思想对架构进行了分离整理，将项目划分为以下四层：

| 层 | 类/文件 | 职责 |
|-----|---------|------|
| 驱动层 | `IrrigationDriver` | 单个引脚的 GPIO 开关封装（pinMode / digitalWrite） |
| 业务层 | `IrrigationService` | 通道状态管理（开/关/查询/JSON 序列化） |
| 控制层 | `WebServerController` | HTTP 路由注册、参数解析、错误码处理 |
| 应用层 | `main.cpp` | 组装各层、初始化、WiFi 连接 |

- 控制层通过依赖注入拿到业务层引用（`IrrigationService&`），不直接操作 GPIO；各层职责单一，便于替换和测试。

#### 2. 单通道 → 多通道升级

最开始是单个引脚控制一处，后决定将原本只控制单个引脚的灌溉系统，升级为支持多通道独立控制。

**为什么用 `std::vector` + `emplace_back`：**

- `new IrrigationDriver[count]` 要求类型有默认构造函数，且无法为每个元素传入不同的引脚参数；
- `emplace_back(pins[i])` 在容器内存上**原地构造**，参数直接传给构造函数，无需默认构造函数；
- vector 自动管理内存（RAII），无需手写 `new[]/delete[]`，避免内存泄漏。

**关键知识点：**

| 概念 | 说明 |
|------|------|
| `std::vector` | 动态数组，连续内存，自动扩容与释放 |
| `emplace_back(参数...)` | 在末尾原地构造元素，参数即构造函数的参数 |
| `reserve(count)` | 提前预留容量，避免多次扩容搬移 |
| `= delete` | 禁用拷贝构造/赋值，防止对象被意外复制（单例语义） |
| 越界校验 | `isValidIndex()` 先判断索引再访问，避免数组越界 |

**接口变化：** 所有操作方法带 `size_t index`，越界返回 `false`；每个通道维护独立的 `isIrrigating` 状态，互不影响。

#### 3. API 设计（配合 docs/api.md）

 我先根据后端逻辑与任务需求设计出对应的 API（路由、参数、错误码），然后结合 AI 设计出合适的前端页面，前后端通过文档约定的接口对接。

**路由表：**

| 方法 | 路径 | 参数 | 说明 |
|------|------|------|------|
| GET | `/irrigation` | 无 | 返回控制页面 HTML |
| GET | `/irrigation/channels` | 无 | 返回通道列表 JSON 数组 |
| POST | `/irrigation/on` | `channel=N` | 开启指定通道 |
| POST | `/irrigation/off` | `channel=N` | 停止指定通道 |
| GET | `/irrigation/status` | 无 / `channel=N` | 全部通道数组 / 单通道对象 |

**错误码语义：**

| 状态码 | 含义 | 场景 |
|--------|------|------|
| `200 OK` | 成功 | 操作完成 |
| `400 Bad Request` | 参数缺失或非法 | 无 channel 参数 / 非数字 |
| `404 Not Found` | 通道不存在 | channel 越界 |
| `409 Conflict` | 状态冲突 | 重复开启 / 重复停止 |

**参数解析要点：** `server.arg("channel")` 取到的是字符串，`String::toInt()` 对非数字输入会静默返回 0，因此先逐字符 `isdigit` 校验，区分"参数非法（400）"与"通道越界（404）"。

---

### 踩坑记录

| 问题 | 原因 | 解决方案 |
|------|------|---------|
| 烧录后页面还是旧 HTML | `uploadfs` 只更新文件系统；浏览器缓存旧页面 | 改 HTML 后必须 `pio run -t uploadfs`；浏览器 Ctrl+F5 强刷 |
| `server.arg()` 编译报错"函数缺少 const 限定符" | 所用 WebServer 库的 `arg()` 不是 const 方法 | 去掉封装函数的 const 限定 |
| `?channel=abc` 被当成通道 0 | `String::toInt()` 对非数字静默返回 0 | 逐字符 `isdigit` 校验后再转换 |
| 页面报 404 File Not Found | 代码里没有调用 `LittleFS.begin()`，文件系统未挂载，很烦人 | 在 `setup()` 中先调用 `LittleFS.begin(true)`（挂载失败自动格式化） |
| 请求页面/灌溉时设备反复崩溃重启，点击有概率失败 | 电脑 USB 口供电不足，WiFi 发射瞬间电流大导致电压跌落，协议栈 panic | 使用独立 5V 电源供电；已实测独立供电稳定 |

### 今日总结

- [x] 完成四层架构的正式项目（main + include）
- [x] 单通道升级为多通道（Service / Controller / 前端）
- [x] 编写多通道 API 文档
- [x] 固件 + 文件系统烧录成功，接口实测全部通过
