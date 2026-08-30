# 嵌入式系统暑期招新任务：ESP32-S3 智能灌溉控制系统

基于 **ESP32-S3 + PlatformIO + Arduino** 的多通道智能灌溉控制系统，覆盖传感器采集、OLED 显示、WiFi 联网、Web 控制、MQTT 云接入、FreeRTOS 多任务、OTA 远程升级等完整物联网开发链路。

## ✨ 功能特性

- **多通道灌溉**：3 路独立 GPIO 控制（`GPIO1/4/8`），互不干扰
- **传感器采集**：DHT22 温湿度（单总线）+ HW-390 土壤湿度（ADC，实测标定）
- **OLED 显示**：SSD1306（I2C `SDA=9 / SCL=10`），三排大字体实时刷新
- **双通道远程控制**：
  - HTTP 页面 `/irrigation`（局域网）
  - MQTT 页面 `/irrigation-mqtt`（WebSocket 直连云端 Broker，可跨网络）
- **MQTT 云接入**：EMQX Cloud Serverless（TLS 8883），5s 数据上报 + 指令下发
- **FreeRTOS 任务化**：5 个任务（sensor / oled / control / mqtt / web）+ 队列通信，控制收敛到唯一执行者
- **AUTO / MANUAL 模式状态机**：自动灌溉（双阈值防抖）+ 手动控制互斥切换
- **配置持久化**：LittleFS `/config.json`（WiFi / MQTT / 阈值 / 默认模式，Web 可改）
- **OTA 远程更新**：A/B 双分区，Web 上传固件，失败自动回滚
- **历史数据**：环形缓冲保存最近 2000 条采样（2s 间隔），`/api/history` 输出

## 📁 文件夹结构

```
├── include/                 # 头文件(按层分类)
│   ├── drivers/             #   硬件驱动: 灌溉/传感器/OLED/MQTT
│   ├── services/            #   业务服务: 传感/灌溉/MQTT/配置/历史
│   ├── controllers/         #   Web API 控制器
│   ├── tasks/               #   FreeRTOS 任务(TaskConfig 公共配置)
│   ├── common_config.h
│   └── wifi_app.h
├── src/
│   ├── main/                # 正式程序(智能灌溉系统)
│   │   ├── drivers/         #   驱动实现
│   │   ├── services/        #   服务实现
│   │   ├── controllers/     #   控制器实现
│   │   ├── tasks/           #   任务实现(sensor/oled/control/mqtt)
│   │   ├── main.cpp         #   程序入口: 组装各层 + 创建任务
│   │   └── wifi_app.cpp
│   └── lab/                 # 练习/测试代码(独立环境编译)
├── data/                    # 文件系统内容(Web 控制页面 HTML)
├── docs/                    # 文档(API/引脚/架构/学习日志)
├── platformio.ini           # PlatformIO 配置(正式 + lab 多环境)
└── README.md
```

## 🏗️ 架构分层

| 层 | 回答的问题 | 主要类 |
| ---- | ---------- | ------ |
| Driver | 硬件**怎么**操作 | `IrrigationDriver` / `EnvSensorDriver` / `SoilSensorDriver` / `OledDisplayDriver` / `MqttDriver` |
| Service | 系统**何时**做、怎么做 | `SensorService` / `IrrigationService` / `MqttService` / `ConfigService` / `HistoryService` |
| Controller | 对外**怎么**暴露 | `WebServerController`（HTTP 路由） |
| Task | 并行**如何**调度 | `sensorTask` / `oledTask` / `controlTask` / `mqttTask`（FreeRTOS） |

控制指令（Web / MQTT / 自动灌溉）统一汇聚到队列，由 `controlTask` **唯一执行**，无并发竞争。

## 📄 文档

**🗺️ 系统架构总览（推荐先看）**：[docs/system-flow-final(visual).html](docs/system-flow-final(visual).html) 一张图完整呈现整个任务的**模块依赖关系与信息流动**——包括传感器数据的上行链路（采样 → 队列 → MQTT/Web 展示）、控制指令的下行链路（Web/MQTT/自动灌溉 → 队列 → `controlTask` 唯一执行）、配置持久化与 OTA 更新流程，以及各模块之间的依赖方向。理解"各个模块之间怎么协作"，先看这张图再读代码，事半功倍。

| 文档 | 说明 |
| ---- | ---- |
| [docs/system-flow-final(visual).html](docs/system-flow-final(visual).html) | 系统架构总览（可视化）：模块依赖 + 信息流动 |
| [docs/api.md](docs/api.md) | HTTP / MQTT 全部接口定义（页面、控制、传感器、配置、历史、OTA） |
| [docs/gpio-pins.md](docs/gpio-pins.md) | 引脚分配说明 |
| [docs/freertos-task-plan.md](docs/freertos-task-plan.md) | FreeRTOS 任务化改造设计 |
| [docs/learning-log.md](docs/learning-log.md) | 学习日志（Day 1 ~ Day 8） |
| [docs/system-flow-final(table).html](docs/system-flow-final(table).html) | 系统架构图（表格版） |

## 🔗 GitHub

- 项目链接：<https://github.com/jijisanqianli/MyCode/tree/main/CODE_Cpp/embedded-system-summer-recruitment>
