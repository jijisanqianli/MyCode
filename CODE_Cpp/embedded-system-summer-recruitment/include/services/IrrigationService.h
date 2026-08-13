#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_IRRIGATION_SERVICE_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_IRRIGATION_SERVICE_H

#include "IrrigationDriver.h"
#include <vector>

// 一个灌溉通道:引脚 + 独立运行状态 + 可选名称
struct IrrigationChannel {
    uint8_t gpioPin;
    bool isIrrigating;
    String name;

    IrrigationChannel(uint8_t pin, const String& channelName = "")
        : gpioPin(pin), isIrrigating(false), name(channelName) {}

    String toJson() const {
        return String("{\"gpioPin\":")
            + gpioPin
            + ",\"status\":"
            + (isIrrigating ? "true" : "false")
            + "}";
    }
};

class IrrigationService {
    std::vector<IrrigationDriver> drivers;    // 每个引脚一个 driver(连续存储,自动管理内存)
    std::vector<IrrigationChannel> channels;  // 通道元数据 + 状态

    bool isValidIndex(size_t index) const;

public:
    explicit IrrigationService(const uint8_t* pins, size_t count);

    // 禁止拷贝:Service 是全局单例,不应被复制
    IrrigationService(const IrrigationService&) = delete;
    IrrigationService& operator=(const IrrigationService&) = delete;

    void begin();

    size_t getChannelCount() const;

    bool turnOnIrrigation(size_t index);
    bool turnOffIrrigation(size_t index);
    bool isIrrigating(size_t index) const;

    const IrrigationChannel& getChannel(size_t index) const;
    void setChannelName(size_t index, const String& name);

    // 状态 JSON:单通道 / 全部通道数组
    String getStatusJson(size_t index) const;
    String getAllStatusJson() const;
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_IRRIGATION_SERVICE_H
