# 🌿 ESP32 智能灌溉控制系统 API 文档

## 1. 基础信息

- **接口协议**：HTTP（局域网直连；远程访问走第 6 章 MQTT 通道）
- **数据格式**：纯文本 (Text) / JSON
- **基准路径 (Base URL)**：`http://<ESP32_IP_ADDRESS>`
- **通道索引 (channel/index)**：从 `0` 开始的整数，对应 `IrrigationService` 中注册的引脚顺序
- **控制收敛说明**：所有控制接口（HTTP on/off/mode、MQTT 指令）统一将指令发往 `manualIrrQueue`，由 `controlTask` 唯一执行，控制行为一致、无并发竞争

## 2. 页面接口

### 2.1 获取 HTTP 控制页面 (HTML)

加载用于操控灌溉系统的嵌入式 Web 界面（页面会根据通道列表动态渲染每个通道的控制按钮，并轮询 `/api/sensors`、`/irrigation/status` 刷新数据）。

- **请求路径**：`/irrigation`
- **HTTP 方法**：`GET`
- **请求参数**：无

#### 响应说明

| **状态码** | **类型**    | **说明**                              |
| ---------- | ----------- | ------------------------------------- |
| `200 OK`   | `text/html` | 返回 LittleFS 中存储的 `irrigation.html` 页面（流式传输） |
| `404 Not Found` | `text/plain` | `File Not Found`（文件系统缺少页面文件） |

### 2.2 获取 MQTT 控制页面 (HTML)

加载纯 MQTT 控制页面（页面通过 WebSocket 直连云端 Broker，不经过 ESP32 的 HTTP API，可远程使用）。

- **请求路径**：`/irrigation-mqtt`
- **HTTP 方法**：`GET`
- **请求参数**：无

#### 响应说明

| **状态码** | **类型**    | **说明**                              |
| ---------- | ----------- | ------------------------------------- |
| `200 OK`   | `text/html` | 返回 LittleFS 中存储的 `irrigation-mqtt.html` 页面 |
| `404 Not Found` | `text/plain` | `File Not Found`（文件系统缺少页面文件） |

### 2.3 获取 OTA 更新页面 (HTML)

返回固件上传页面（页面内嵌于固件中，独立于文件系统，文件系统损坏时仍可用于救砖）。

- **请求路径**：`/update`
- **HTTP 方法**：`GET`
- **请求参数**：无

#### 响应说明

| **状态码** | **类型**    | **说明**                              |
| ---------- | ----------- | ------------------------------------- |
| `200 OK`   | `text/html` | 返回内嵌 OTA 上传表单页面              |

## 3. 通道控制 API

### 3.1 获取通道列表

返回系统注册的全部灌溉通道（索引、引脚、名称），前端据此动态渲染控制界面。

- **请求路径**：`/irrigation/channels`
- **HTTP 方法**：`GET`
- **响应格式**：`application/json`

#### 响应示例

```json
[
  {"index": 0, "gpioPin": 1, "name": "1号电磁阀"},
  {"index": 1, "gpioPin": 4, "name": "2号电磁阀"}
]
```

#### 字段说明

| **字段**  | **类型** | **说明**                     |
| --------- | -------- | ---------------------------- |
| `index`   | `number` | 通道索引，作为后续接口的参数 |
| `gpioPin` | `number` | 该通道控制的 GPIO 引脚编号   |
| `name`    | `string` | 通道名称（未设置时为空字符串）|

#### 响应说明

| **状态码** | **类型**           | **说明**             |
| ---------- | ------------------ | -------------------- |
| `200 OK`   | `application/json` | 返回通道列表 JSON 数组 |

### 3.2 开启灌溉

请求开启指定通道灌溉。**注意：接口仅表示"请求已接受"**（指令入队 `manualIrrQueue`），实际动作由 `controlTask` 执行，随后执行会自动切换为手动模式。

- **请求路径**：`/irrigation/on`
- **HTTP 方法**：`POST`
- **请求参数**：

| **参数**  | **类型** | **必填** | **说明**                           |
| --------- | -------- | -------- | ---------------------------------- |
| `channel` | `number` | 是       | 要开启的通道索引，如 `?channel=1`  |

#### 响应说明

- **Content-Type**: `text/plain`

| **状态码**     | **返回示例**                       | **说明**                 |
| -------------- | ---------------------------------- | ------------------------ |
| `200 OK`       | `Irrigation start requested (channel 1)` | 请求已入队，等待 `controlTask` 执行 |
| `400 Bad Request` | `Missing or invalid channel parameter` | 参数缺失或不是合法数字 |
| `404 Not Found` | `Channel not found`                | 通道索引超出范围         |

### 3.3 停止灌溉

请求停止指定通道灌溉。同 3.2，入队后由 `controlTask` 执行。

- **请求路径**：`/irrigation/off`
- **HTTP 方法**：`POST`
- **请求参数**：

| **参数**  | **类型** | **必填** | **说明**                           |
| --------- | -------- | -------- | ---------------------------------- |
| `channel` | `number` | 是       | 要关闭的通道索引，如 `?channel=1`  |

#### 响应说明

- **Content-Type**: `text/plain`

| **状态码**     | **返回示例**                       | **说明**                 |
| -------------- | ---------------------------------- | ------------------------ |
| `200 OK`       | `Irrigation stop requested (channel 1)` | 请求已入队，等待 `controlTask` 执行 |
| `400 Bad Request` | `Missing or invalid channel parameter` | 参数缺失或不是合法数字 |
| `404 Not Found` | `Channel not found`                | 通道索引超出范围         |

### 3.4 切换控制模式

在自动灌溉（AUTO）与手动控制（MANUAL）之间切换。指令同样入队 `manualIrrQueue` 执行。

- **请求路径**：`/irrigation/mode`
- **HTTP 方法**：`POST`
- **请求参数**：

| **参数**  | **类型** | **必填** | **说明**                           |
| --------- | -------- | -------- | ---------------------------------- |
| `mode`    | `string` | 是       | `auto`（自动灌溉）或 `manual`（手动） |

#### 响应说明

- **Content-Type**: `text/plain`

| **状态码**     | **返回示例**                       | **说明**                 |
| -------------- | ---------------------------------- | ------------------------ |
| `200 OK`       | `mode switch requested: auto`      | 模式切换请求已入队       |
| `400 Bad Request` | `mode must be auto or manual`   | 参数不是 `auto` 或 `manual` |

### 3.5 查询通道状态

获取通道的当前灌溉状态（用于前端自动刷新）。

- **请求路径**：`/irrigation/status`
- **HTTP 方法**：`GET`

#### 3.5.1 查询全部通道状态（无参数）

- **请求参数**：无
- **响应格式**：`application/json`

```json
[
  {"gpioPin": 1, "status": true},
  {"gpioPin": 4, "status": false}
]
```

#### 3.5.2 查询单个通道状态（带参数）

- **请求参数**：

| **参数**  | **类型** | **必填** | **说明**                           |
| --------- | -------- | -------- | ---------------------------------- |
| `channel` | `number` | 是       | 要查询的通道索引，如 `?channel=1`  |

- **响应格式**：`application/json`

```json
{"gpioPin": 4, "status": false}
```

#### 字段说明（两种查询共用）

| **字段**  | **类型** | **说明**                     |
| --------- | -------- | ---------------------------- |
| `gpioPin` | `number` | 该通道控制的 GPIO 引脚编号   |
| `status`  | `bool`   | true 表示正在灌溉，false 表示没有灌溉 |

#### 响应说明

| **状态码**     | **类型**           | **说明**                       |
| -------------- | ------------------ | ------------------------------ |
| `200 OK`       | `application/json` | 返回全部通道状态数组 / 指定通道状态对象 |
| `400 Bad Request` | `text/plain`    | `Missing or invalid channel parameter`（带 channel 参数但非法） |
| `404 Not Found` | `text/plain`      | `Channel not found`（带 channel 参数但越界） |

## 4. 数据查询 API

### 4.1 获取传感器数据

返回当前环境传感器数据（温度、湿度、土壤湿度）与当前控制模式。数据由 `SensorService` 每 2s 周期采样并缓存，查询实时返回缓存值。

- **请求路径**：`/api/sensors`
- **HTTP 方法**：`GET`
- **请求参数**：无
- **响应格式**：`application/json`

#### 响应示例

```json
{"temperature":28.9,"humidity":64.4,"soil":2,"mode":"auto"}
```

#### 字段说明

| **字段**        | **类型**     | **说明**                                   |
| --------------- | ------------ | ------------------------------------------ |
| `temperature`   | `number`/`null` | 温度（°C），传感器读取失败时为 `null`    |
| `humidity`      | `number`/`null` | 相对湿度（%），传感器读取失败时为 `null` |
| `soil`          | `number`/`null` | 土壤湿度（0~100%），尚未采样时为 `null`  |
| `mode`          | `string`     | 当前控制模式：`auto` / `manual`            |

#### 响应说明

| **状态码** | **类型**           | **说明**                     |
| ---------- | ------------------ | ---------------------------- |
| `200 OK`   | `application/json` | 返回传感器数据 JSON 对象     |

#### 前端使用

页面 `data/irrigation.html` 每 2s 轮询该接口刷新顶部传感器卡片（温度/湿度/土壤/模式）。

### 4.2 获取历史数据

返回最近一段时间的历史采样序列（环形缓冲存储，2s 一条，共 2000 条 ≈ 66 分钟，重启后清空），供前端绘制趋势曲线。

- **请求路径**：`/api/history`
- **HTTP 方法**：`GET`
- **请求参数**：

| **参数**  | **类型** | **必填** | **说明**                           |
| --------- | -------- | -------- | ---------------------------------- |
| `limit`   | `number` | 否       | 返回条数上限，默认 `120`，最大 `2000`（当前已存条数） |

- **响应格式**：`application/json`

#### 响应示例

```json
[
  {"ts": 1723456789, "t": 28.90, "h": 64.40, "s": 30},
  {"ts": 1723456791, "t": 28.90, "h": 64.40, "s": 30}
]
```

#### 字段说明

| **字段** | **类型** | **说明**                     |
| -------- | -------- | ---------------------------- |
| `ts`     | `number` | 采样时刻（`millis()` 毫秒时间戳） |
| `t`      | `number` | 温度（°C），2 位小数         |
| `h`      | `number` | 湿度（%），2 位小数          |
| `s`      | `number` | 土壤湿度（0~100%）           |

#### 响应说明

| **状态码** | **类型**           | **说明**                     |
| ---------- | ------------------ | ---------------------------- |
| `200 OK`   | `application/json` | 返回历史数据 JSON 数组（时间序：最旧→最新） |

### 4.3 配置管理接口

读取/更新持久化配置（WiFi / MQTT / 灌溉阈值 / 默认模式），配置保存于 LittleFS 的 `/config.json`。

#### 4.3.1 读取配置

- **请求路径**：`/api/config`
- **HTTP 方法**：`GET`
- **请求参数**：无
- **响应格式**：`application/json`

```json
{"wifiSsid":"SDK","wifiPassword":"13730708827","mqttBroker":"i3daab3b.ala.cn-shenzhen.emqxsl.cn","mqttPort":8883,"mqttUsername":"esp32-s3","mqttPassword":"123654789","dryThreshold":30,"wetThreshold":60,"defaultMode":"auto"}
```

#### 4.3.2 更新配置

- **请求路径**：`/api/config`
- **HTTP 方法**：`POST`
- **请求体**：JSON（**只更新消息中存在的字段**，缺省字段保持原值）

示例（只改灌溉阈值）：

```json
{"dryThreshold":20,"wetThreshold":50}
```

#### 响应说明

| **状态码** | **类型** | **说明** |
| ---------- | -------- | -------- |
| `200 OK` | `text/plain` | `config saved, reboot to apply` |
| `400 Bad Request` | `text/plain` | `empty config body`（请求体为空）/ `config parse/save failed`（解析或保存失败） |

#### 字段说明

| **字段** | **类型** | **说明** |
| -------- | -------- | -------- |
| `wifiSsid` / `wifiPassword` | `string` | WiFi 连接凭证（变更需重启生效） |
| `mqttBroker` / `mqttPort` / `mqttUsername` / `mqttPassword` | `string`/`number` | MQTT Broker 连接配置（变更需重启生效） |
| `dryThreshold` / `wetThreshold` | `number` | 自动灌溉双阈值（土壤湿度低于 dry 开泵，高于 wet 关泵，下次启动生效） |
| `defaultMode` | `string` | 开机默认模式：`auto` / `manual`（下次启动生效） |

## 5. OTA 固件更新 API

上传新固件 `.bin` 完成远程升级。固件写入非运行分区，校验通过后自动切换并重启；失败自动回滚旧固件（A/B 双分区）。

- **请求路径**：`/update`
- **HTTP 方法**：`POST`
- **请求体**：`multipart/form-data`

| **字段** | **类型** | **必填** | **说明** |
| -------- | -------- | -------- | -------- |
| `update` | `file` | 是 | 固件文件（`.bin`），即 `pio run` 生成的 `firmware.bin` |
| URL 参数 `key` | `string` | 是 | 更新密钥，拼在 URL 上（如 `/update?key=ota2026`），错误则中止上传 |

> 前端使用：访问 `GET /update` 获取上传页面，页面会将输入的密钥自动拼到表单 action 的 `?key=` 后提交。

#### 响应说明

| **状态码** | **类型** | **说明** |
| ---------- | -------- | -------- |
| `200 OK` | `text/plain` | `Update OK, rebooting...`（校验通过，500ms 后自动重启） |
| `500 Internal Server Error` | `text/plain` | `Update FAILED`（写入/校验失败） |

## 6. MQTT 接口（云端通道）

ESP32 通过 MQTT 连接 EMQX Cloud Serverless Broker，实现**数据上报**与**指令下发**（与 HTTP 并行，控制权统一收敛到 `controlTask`）。MQTT 通道不受局域网限制，可用于远程访问与控制。

### 6.1 连接信息

| 项 | 值 |
| --- | --- |
| Broker 地址 | `i3daab3b.ala.cn-shenzhen.emqxsl.cn` |
| 端口 | `8883`（MQTT over TLS，网页端 WSS 为 `8084`） |
| 认证 | 用户名/密码（部署侧配置） |
| Client ID | `esp32-s3-irrigation`（同一 Broker 下需唯一） |

### 6.2 数据上报主题（设备发布 / 客户端订阅）

**主题**：`garden/esp32-s3/data`

ESP32 每 5s 发布一次传感器数据、控制模式与通道状态（客户端订阅该主题即可接收）：

```json
{"device":"esp32-s3","temperature":28.9,"humidity":64.4,"soil":2,"mode":"auto","channels":[{"index":0,"status":false},{"index":1,"status":false}]}
```

| 字段 | 类型 | 说明 |
| ---- | ---- | ---- |
| `device` | `string` | 设备标识 |
| `temperature` | `number` | 温度（°C） |
| `humidity` | `number` | 湿度（%） |
| `soil` | `number` | 土壤湿度（0~100%） |
| `mode` | `string` | 当前控制模式：`auto` / `manual` |
| `channels` | `array` | 各通道实时状态：`{"index":N,"status":bool}` |

> 注：设备连接成功后会对控制主题发布一次**空 retain 消息**，清除 Broker 上历史保留指令，防止旧指令重放导致"启动即开泵"。

### 6.3 控制指令主题（客户端发布 / 设备订阅）

**主题**：`garden/esp32-s3/cmd`

客户端向该主题发布指令，ESP32 解析后执行（控制权收敛到 `controlTask`）：

| 指令 JSON | 效果 |
| --------- | ---- |
| `{"pump":"on","index":0}` | 开启通道 0 灌溉，**并自动切换为手动模式** |
| `{"pump":"off","index":1}` | 关闭通道 1 灌溉，并自动切换为手动模式 |
| `{"mode":"auto"}` | 切换为自动灌溉模式（土壤低于阈值自动开泵） |
| `{"mode":"manual"}` | 切换为手动控制模式（自动灌溉停止判断） |

**模式规则**：
- 开机默认 **auto**（自动灌溉：土壤 < 30% 开泵，> 60% 关泵，双阈值防抖；阈值可通过 `/api/config` 修改）
- 任何 `pump` 指令隐含切换为 `manual`
- 回到自动模式需显式发送 `{"mode":"auto"}`

### 6.4 HTTP 与 MQTT 对照

| 功能 | HTTP | MQTT |
| ---- | ---- | ---- |
| 获取传感器数据 | `GET /api/sensors` | 订阅 `garden/esp32-s3/data`（实时推送，含 mode/channels） |
| 获取历史数据 | `GET /api/history?limit=N` | —（暂无 MQTT 通道） |
| 控制灌溉 | `POST /irrigation/on?channel=N` | 发布 `{"pump":"on","index":N}` |
| 切换模式 | `POST /irrigation/mode?mode=auto` | 发布 `{"mode":"auto"}` |
| 远程升级 | `POST /update`（需局域网） | —（暂无 MQTT OTA 通道） |

> 注：HTTP 控制路由最终同样将指令发往 `manualIrrQueue`，与 MQTT 指令汇聚到同一个执行者（`controlTask`），保证控制行为一致、无并发竞争。
