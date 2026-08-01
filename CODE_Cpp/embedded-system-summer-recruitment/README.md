# 嵌入式系统暑期招新任务

基于 **ESP32-S3 + PlatformIO** 的智能灌溉控制系统(多通道),为暑期招新任务项目文件夹。

## 📁 文件夹结构

```
├── include/        # 头文件(声明)
├── src/
│   ├── main/       # 正式程序(智能灌溉系统)
│   └── lab/        # 练习/测试代码
├── data/           # 文件系统内容(Web 控制页面 HTML)
├── docs/           # API 文档、学习日志
├── test/           # 测试
├── lib/            # 库说明
├── platformio.ini  # PlatformIO 配置
└── README.md
```

## 使用

```powershell
pio run -t upload -t uploadfs -e app-main   # 编译并烧录固件 + 文件系统
```

详情见 [docs/api.md](docs/api.md)。
