# FreeRTOS 任务化改造计划

> 阶段五：把现有"单循环轮询"改造为"多任务 + 队列"架构。
> 配套可视化：[architecture.html](architecture.html)

## 1. 目标架构

### 1.1 任务定义

| 任务 | 核 | 优先级 | 周期 | 职责 | 通信 |
|------|----|--------|------|------|------|
| `sensorTask` | 0 | 2 | 2000ms | 采样 DHT22 + 土壤，组装 `SensorData_t` | 发 oledQueue / controlQueue |
| `mqttTask` | 0 | 2 | 5000ms 上报 | MQTT 连接/上报/收指令（**peek latestDataQueue** 取最新值） | 收指令发 manualIrrQueue |
| `controlTask` | 1 | **3(最高)** | 事件驱动 | 自动灌溉 + 云端/Web 指令执行（**唯一执行者**） | 收 autoIrrQueue + manualIrrQueue |
| `oledTask` | 1 | 1 | 事件驱动 | 收数据刷新 OLED | 收 oledQueue |
| `loopTask` | 0 | 1 | 异步 | Web 服务器（Arduino 主循环） | HTTP（不经过队列） |

### 1.2 队列

| 队列 | 容量 | 生产者 | 消费者 | 数据 |
|------|------|--------|--------|------|
| `oledQueue` | 10 | sensorTask | oledTask | `SensorData_t`（每次采样, 事件驱动显示） |
| `latestDataQueue` | **1** | sensorTask（`xQueueOverwrite` 覆盖写） | mqttTask（`xQueuePeek` 读最新） | `SensorData_t`（最新值快照, 保证同一次采样一致性） |
| `autoIrrQueue` | 10 | sensorTask | controlTask | `SensorData_t`（自动灌溉判断触发） |
| `manualIrrQueue` | 5 | mqttTask / WebServerController | controlTask | `Command_t`（手动指令） |

### 1.3 数据流

```
sensorTask ──► oledQueue ──► oledTask ──► OledDisplayDriver
        ──► latestDataQueue(overwrite) ──► mqttTask(peek) ──► MqttService ──► Broker
        ──► autoIrrQueue ──► controlTask(自动灌溉判断) ──► IrrigationService
Broker 指令 ──► mqttTask ──► manualIrrQueue ──► controlTask
Web 指令 ──► WebServerController ──► manualIrrQueue ──► controlTask
```

## 2. 文件规划

```
include/
├── tasks/                  ★ 新增
│   ├── TaskConfig.h        # 任务宏/结构体/队列句柄
│   ├── sensorTask.h        # 任务声明
│   ├── mqttTask.h
│   ├── controlTask.h
│   └── oledTask.h
├── drivers/                # 已有, 不动
├── services/               # 已有(仅 MqttService 微调)
└── controllers/            # 已有(仅 WebServerController 微调)

src/main/
├── main.cpp                # 改造: 组装 + 创建队列 + 启动任务
├── tasks/                  ★ 新增(实现)
│   ├── sensorTask.cpp
│   ├── mqttTask.cpp
│   ├── controlTask.cpp
│   └── oledTask.cpp
├── drivers/                # 已有, 不动
├── services/               # 已有
└── controllers/            # 已有
```

## 3. 关键设计决策

### 3.1 队列"广播"陷阱 → 每消费者独立队列

FreeRTOS 队列是**单消费者**：一个数据只能被一个任务取走。若让两个任务消费同一队列，会竞争取数据、互相饿死。

**解法**：
- **消费型任务**（要取走数据处理的）：各配独立队列 —— `oledQueue`(OLED)、`autoIrrQueue`(自动灌溉)
- **只读最新值任务**（不消费数据）：单位置队列 + `xQueueOverwrite`/`xQueuePeek` —— `latestDataQueue` 容量 1，sensorTask 覆盖写，mqttTask 偷看

**为什么 mqttTask 用单位置队列而不是裸变量**：裸变量分字段读会产生"混合快照"（三个字段来自不同采样轮次，数据不自洽）；队列一次拷贝**完整结构体**，保证同一次采样的三个值一致。

### 3.2 控制收敛（唯一执行者）

Web / MQTT / 自动灌溉三路控制指令**统一进 cmdQueue**，只有 `controlTask` 真正调用 `IrrigationService`：

- `MqttService::onCommand()`：从"直接调 IrrigationService"改为"发 cmdQueue"
- `WebServerController` 控制路由：同样改为"发 cmdQueue"
- 好处：控制动作天然串行，无并发竞争，无需到处加锁

### 3.3 队列 vs 缓存（最新值 vs 事件）

| 类型 | 数据 | 方式 |
|------|------|------|
| 事件型（每次都要处理） | OLED 显示、自动灌溉判断、控制指令 | 队列（阻塞接收） |
| 最新值（周期取一次） | MQTT 上报 | 单位置队列 + `xQueueOverwrite`/`xQueuePeek` |

`sensorTask` 每次采样：① 组装完整 `SensorData_t` ② 发 oledQueue/autoIrrQueue ③ `xQueueOverwrite` 覆盖 latestDataQueue。

### 3.4 共享资源保护

- 数据全走队列（值拷贝）→ 无共享变量竞争
- `Serial` 打印：多任务会乱 → 封装互斥锁日志函数
- OLED：仅 oledTask 独占，无需锁
- GPIO/灌溉：仅 controlTask 操作，无需锁
- 例外：`WebServerController` 查状态时读 Service 缓存 → 用 `volatile` + 短临界区

## 4. 实施步骤

### Step 0 · 备份（已完成 ✅）
项目文件夹已整体备份。

### Step 1 · `TaskConfig.h`（公共中枢）
- 任务参数宏（优先级/核/栈）、`SensorData_t`、`Command_t` 结构体、队列句柄 extern
- 验证：编译通过

### Step 2 · 最小闭环：sensorTask → oledQueue → oledTask
- 新建 `sensorTask`（核0 P2 2s）：采样 → 更新缓存 + 发 oledQueue
- 新建 `oledTask`（核1 P1）：收 oledQueue → 刷新 OLED
- main.cpp：创建队列 + 启动两任务；移除 loop 里 sensorService.update() 和 OLED 刷新
- 验证：OLED 正常三排大字体显示、无崩溃

### Step 3 · `controlTask`（自动灌溉 + 指令执行）
- 新建 `controlTask`（核1 **P3**）：队列集同时等待 autoIrrQueue（自动灌溉触发）+ manualIrrQueue（手动指令）
- 自动灌溉：土壤湿度 < 阈值开泵，恢复后关泵（双阈值防抖）
- 验证：土壤湿度变化 → LED 自动开关

### Step 4 · `mqttTask` + 控制收敛
- 新建 `mqttTask`（核0 P2）：连接/5s 上报（peek latestDataQueue）/收指令 → 发 manualIrrQueue
- 微调 `MqttService::onCommand`：改发 manualIrrQueue
- 微调 `WebServerController` 控制路由：改发 manualIrrQueue
- 验证：MQTTX / 网页指令都经 controlTask 执行（串口日志确认）

### Step 5 · main.cpp 整合
- 启动全部任务；loop() 只留 `webServerController.handleClient()`
- 按实际运行调栈大小/优先级
- 验证：全功能回归（传感器/OLED/MQTT/Web/自动灌溉并行正常）

### Step 6 · 收尾
- 栈溢出排查、心跳日志确认稳定
- 更新 docs + 学习笔记

## 5. 风险与注意事项

| 风险 | 对策 |
|------|------|
| 任务栈溢出 → 崩溃重启 | 栈先给 4096，`SensorData_t` 传值拷贝用栈 |
| 共享缓存数据竞争 | volatile + 短临界区（或互斥锁） |
| Serial 多任务打印乱 | 日志封装互斥锁 |
| mqttTask 上报阻塞拖慢指令 | mqtt.loop() 高频调用，publish 不阻塞 |
| 自动灌溉阈值抖动 | 双阈值（滞回）判断 |

## 6. 参考资料

- [architecture.html](architecture.html)：任务/队列/分层可视化
- `src/lab/freertos_task_test.cpp`：生产者-消费者队列练手
