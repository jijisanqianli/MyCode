# 🌿 ESP32 智能灌溉控制系统 API 文档

## 1. 基础信息

- **接口协议**：HTTP / HTTPS
- **数据格式**：纯文本 (Text) / JSON
- **基准路径 (Base URL)**：`http://<ESP32_IP_ADDRESS>`
- **通道索引 (channel)**：从 `0` 开始的整数，对应 `IrrigationService` 中注册的引脚顺序

## 2. 接口列表

### 2.1 获取控制页面 (HTML)

加载用于操控灌溉系统的嵌入式 Web 界面（页面会根据通道列表动态渲染每个通道的控制按钮）。

- **请求路径**：`/irrigation`
- **HTTP 方法**：`GET`
- **请求头**：无
- **请求参数**：无

#### 响应说明

| **状态码** | **类型**    | **说明**                              |
| ---------- | ----------- | ------------------------------------- |
| `200 OK`   | `text/html` | 返回 ESP32 内存中存储的静态 HTML 页面 |

### 2.2 获取通道列表

返回系统注册的全部灌溉通道（索引、引脚、名称），前端据此动态渲染控制界面。

- **请求路径**：`/irrigation/channels`
- **HTTP 方法**：`GET`
- **响应格式**：`application/json`

#### 响应示例

```json
[
  {"index": 0, "gpioPin": 4, "name": "1号电磁阀"},
  {"index": 1, "gpioPin": 5, "name": "2号电磁阀"}
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

### 2.3 开启灌溉 (点亮 LED)

控制 ESP32 将指定通道的 GPIO 引脚拉高，开启灌溉继电器/LED。

- **请求路径**：`/irrigation/on`
- **HTTP 方法**：`POST`
- **请求头**：无
- **请求参数**：

| **参数**  | **类型** | **必填** | **说明**                           |
| --------- | -------- | -------- | ---------------------------------- |
| `channel` | `number` | 是       | 要开启的通道索引，如 `?channel=1`  |

#### 响应说明

- **Content-Type**: `text/plain`

| **状态码**     | **返回示例**                       | **说明**                 |
| -------------- | ---------------------------------- | ------------------------ |
| `200 OK`       | `Irrigation started (channel 1)`   | 指定通道开启成功         |
| `400 Bad Request` | `Missing or invalid channel parameter` | 参数缺失或不是合法数字 |
| `404 Not Found` | `Channel not found`                | 通道索引超出范围         |
| `409 Conflict` | `Channel already running`          | 该通道已是打开状态       |

### 2.4 停止灌溉 (熄灭 LED)

控制 ESP32 将指定通道的 GPIO 引脚拉低，关闭灌溉继电器/LED。

- **请求路径**：`/irrigation/off`
- **HTTP 方法**：`POST`
- **请求头**：无
- **请求参数**：

| **参数**  | **类型** | **必填** | **说明**                           |
| --------- | -------- | -------- | ---------------------------------- |
| `channel` | `number` | 是       | 要关闭的通道索引，如 `?channel=1`  |

#### 响应说明

- **Content-Type**: `text/plain`

| **状态码**     | **返回示例**                       | **说明**                 |
| -------------- | ---------------------------------- | ------------------------ |
| `200 OK`       | `Irrigation stopped (channel 1)`   | 指定通道停止成功         |
| `400 Bad Request` | `Missing or invalid channel parameter` | 参数缺失或不是合法数字 |
| `404 Not Found` | `Channel not found`                | 通道索引超出范围         |
| `409 Conflict` | `Channel not running`              | 该通道已是停止状态       |

## 3. 状态查询 API

### 3.1 查询全部通道状态

获取所有通道的当前灌溉状态（用于前端自动刷新）。

- **请求路径**：`/irrigation/status`
- **HTTP 方法**：`GET`
- **请求参数**：无
- **响应格式**：`application/json`

#### 响应示例

```json
[
  {"gpioPin": 4, "status": true},
  {"gpioPin": 5, "status": false}
]
```

#### 字段说明

| **字段**  | **类型** | **说明**                     |
| --------- | -------- | ---------------------------- |
| `gpioPin` | `number` | 该通道控制的 GPIO 引脚编号   |
| `status`  | `bool`   | true 表示正在灌溉，false 表示没有灌溉 |

#### 响应说明

| **状态码** | **类型**           | **说明**                   |
| ---------- | ------------------ | -------------------------- |
| `200 OK`   | `application/json` | 返回全部通道状态的 JSON 数组 |

### 3.2 查询单个通道状态

获取指定通道的当前灌溉状态。

- **请求路径**：`/irrigation/status`
- **HTTP 方法**：`GET`
- **请求参数**：

| **参数**  | **类型** | **必填** | **说明**                           |
| --------- | -------- | -------- | ---------------------------------- |
| `channel` | `number` | 是       | 要查询的通道索引，如 `?channel=1`  |

- **响应格式**：`application/json`

#### 响应示例

```json
{"gpioPin": 5, "status": false}
```

#### 响应说明

| **状态码**     | **类型**           | **说明**                       |
| -------------- | ------------------ | ------------------------------ |
| `200 OK`       | `application/json` | 返回指定通道的状态 JSON 对象   |
| `400 Bad Request` | `text/plain`    | `Missing or invalid channel parameter` |
| `404 Not Found` | `text/plain`      | `Channel not found`            |

## 4. 传感器数据 API

### 4.1 获取传感器数据

返回当前环境传感器数据（温度、湿度、土壤湿度）。数据由 `SensorService` 每 2s 周期采样并缓存，查询实时返回缓存值。

- **请求路径**：`/api/sensors`
- **HTTP 方法**：`GET`
- **请求参数**：无
- **响应格式**：`application/json`

#### 响应示例

```json
{"temperature":28.9,"humidity":64.4,"soil":2}
```

#### 字段说明

| **字段**        | **类型**     | **说明**                                   |
| --------------- | ------------ | ------------------------------------------ |
| `temperature`   | `number`/`null` | 温度（°C），传感器读取失败时为 `null`    |
| `humidity`      | `number`/`null` | 相对湿度（%），传感器读取失败时为 `null` |
| `soil`          | `number`/`null` | 土壤湿度（0~100%），尚未采样时为 `null`  |

#### 响应说明

| **状态码** | **类型**           | **说明**                     |
| ---------- | ------------------ | ---------------------------- |
| `200 OK`   | `application/json` | 返回传感器数据 JSON 对象     |

#### 前端使用

页面 `data/irrigation.html` 每 2s 轮询该接口刷新顶部传感器卡片（温度/湿度/土壤/模式）。

### 4.2 配置管理接口

读取/更新持久化配置（WiFi / MQTT / 灌溉阈值 / 默认模式），配置保存于 LittleFS 的 `/config.json`。

#### 4.2.1 读取配置

- **请求路径**：`/api/config`
- **HTTP 方法**：`GET`
- **请求参数**：无
- **响应格式**：`application/json`

```json
{"wifiSsid":"SDK","wifiPassword":"13730708827","mqttBroker":"i3daab3b.ala.cn-shenzhen.emqxsl.cn","mqttPort":8883,"mqttUsername":"esp32-s3","mqttPassword":"123654789","dryThreshold":30,"wetThreshold":60,"defaultMode":"auto"}
```

#### 4.2.2 更新配置

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
| `400 Bad Request` | `text/plain` | 请求体为空 / 解析或保存失败 |

#### 字段说明

| **字段** | **类型** | **说明** |
| -------- | -------- | -------- |
| `wifiSsid` / `wifiPassword` | `string` | WiFi 连接凭证（变更需重启生效） |
| `mqttBroker` / `mqttPort` / `mqttUsername` / `mqttPassword` | `string`/`number` | MQTT Broker 连接配置（变更需重启生效） |
| `dryThreshold` / `wetThreshold` | `number` | 自动灌溉双阈值（土壤湿度低于 dry 开泵，高于 wet 关泵，下次启动生效） |
| `defaultMode` | `string` | 开机默认模式：`auto` / `manual`（下次启动生效） |

## 5. MQTT 接口（云端通道）

ESP32 通过 MQTT 连接 EMQX Cloud Serverless Broker，实现**数据上报**与**指令下发**（与 HTTP 并行，控制权统一收敛到 `controlTask`）。

### 5.1 连接信息

| 项 | 值 |
| --- | --- |
| Broker 地址 | `i3daab3b.ala.cn-shenzhen.emqxsl.cn` |
| 端口 | `8883`（MQTT over TLS） |
| 认证 | 用户名/密码（部署侧配置） |
| Client ID | `esp32-s3-irrigation`（同一 Broker 下需唯一） |

### 5.2 数据上报主题（订阅）

**主题**：`garden/esp32-s3/data`

ESP32 每 5s 发布一次传感器数据（客户端订阅该主题即可接收）：

```json
{"device":"esp32-s3","temperature":28.9,"humidity":64.4,"soil":2,"mode":"auto"}
```

| 字段 | 类型 | 说明 |
| ---- | ---- | ---- |
| `device` | `string` | 设备标识 |
| `temperature` | `number` | 温度（°C） |
| `humidity` | `number` | 湿度（%） |
| `soil` | `number` | 土壤湿度（0~100%） |
| `mode` | `string` | 当前控制模式：`auto` / `manual` |

### 5.3 控制指令主题（发布）

**主题**：`garden/esp32-s3/cmd`

客户端向该主题发布指令，ESP32 解析后执行（控制权收敛到 `controlTask`）：

| 指令 JSON | 效果 |
| --------- | ---- |
| `{"pump":"on","index":0}` | 开启通道 0 灌溉，**并自动切换为手动模式** |
| `{"pump":"off","index":1}` | 关闭通道 1 灌溉，并自动切换为手动模式 |
| `{"mode":"auto"}` | 切换为自动灌溉模式（土壤低于阈值自动开泵） |
| `{"mode":"manual"}` | 切换为手动控制模式（自动灌溉停止判断） |

**模式规则**：
- 开机默认 **auto**（自动灌溉：土壤 < 30% 开泵，> 60% 关泵，双阈值防抖）
- 任何 `pump` 指令隐含切换为 `manual`
- 回到自动模式需显式发送 `{"mode":"auto"}`

### 5.4 HTTP 与 MQTT 对照

| 功能 | HTTP | MQTT |
| ---- | ---- | ---- |
| 获取传感器数据 | `GET /api/sensors` | 订阅 `garden/esp32-s3/data`（实时推送） |
| 控制灌溉 | `POST /irrigation/on?channel=N` | 发布 `{"pump":"on","index":N}` |
| 切换模式 | `POST /irrigation/mode?mode=auto` | 发布 `{"mode":"auto"}` |

> 注：HTTP 控制路由最终同样将指令发往 `manualIrrQueue`，与 MQTT 指令汇聚到同一个执行者（`controlTask`），保证控制行为一致、无并发竞争。
