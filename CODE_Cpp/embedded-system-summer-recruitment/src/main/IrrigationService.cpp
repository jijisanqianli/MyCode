#include "IrrigationService.h"

IrrigationService::IrrigationService(const uint8_t* pins, size_t count) {
    // 一次性预留容量,避免 emplace_back 过程中触发多次扩容搬移
    drivers.reserve(count);
    channels.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        drivers.emplace_back(pins[i]);   // 原地构造,无需默认构造函数
        channels.emplace_back(pins[i]);  // 原地构造
    }
}

void IrrigationService::begin() {
    for (size_t i = 0; i < channels.size(); ++i) {
        drivers[i].init();
        channels[i].isIrrigating = false;
    }
}

size_t IrrigationService::getChannelCount() const {
    return channels.size();
}

bool IrrigationService::isValidIndex(size_t index) const {
    return index < channels.size();
}

bool IrrigationService::turnOnIrrigation(size_t index) {
    if (!isValidIndex(index)) return false;
    if (channels[index].isIrrigating) return false;

    drivers[index].setState(true);
    channels[index].isIrrigating = true;
    return true;
}

bool IrrigationService::turnOffIrrigation(size_t index) {
    if (!isValidIndex(index)) return false;
    if (!channels[index].isIrrigating) return false;

    drivers[index].setState(false);
    channels[index].isIrrigating = false;
    return true;
}

bool IrrigationService::isIrrigating(size_t index) const {
    if (!isValidIndex(index)) return false;
    return channels[index].isIrrigating;
}

const IrrigationChannel& IrrigationService::getChannel(size_t index) const {
    return channels[index];
}

void IrrigationService::setChannelName(size_t index, const String& name) {
    if (!isValidIndex(index)) return;
    channels[index].name = name;
}

String IrrigationService::getStatusJson(size_t index) const {
    if (!isValidIndex(index)) return String("{}");
    return channels[index].toJson();
}

String IrrigationService::getAllStatusJson() const {
    String json = "[";
    for (size_t i = 0; i < channels.size(); ++i) {
        if (i > 0) json += ",";
        json += channels[i].toJson();
    }
    json += "]";
    return json;
}
