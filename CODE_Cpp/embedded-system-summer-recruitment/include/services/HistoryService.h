#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_HISTORY_SERVICE_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_HISTORY_SERVICE_H

#include <Arduino.h>
#include "TaskConfig.h"   // SensorData_t

// 历史数据服务: 环形缓冲保存最近 N 条采样(内存, 重启丢失)
// 2s 降频存储(2000 条 ≈ 66 分钟), 供 /api/history 与前端曲线展示
class HistoryService {
    static constexpr size_t MAX_POINTS = 2000;             // 环形缓冲容量(2000×16B ≈ 32KB RAM)
    static constexpr uint32_t SAMPLE_INTERVAL_MS = 2000;   // 存储间隔(与采样同步, 2s)

    SensorData_t buffer[MAX_POINTS];   // 环形缓冲(固定数组, 无动态分配)
    size_t head  = 0;                  // 下一个写入位置
    size_t count = 0;                  // 当前有效条数
    uint32_t lastAddMs = 0;            // 降频节流时间戳

public:
    // 降频存储: 距上次 >= 30s 才写入(旧数据被覆盖)
    void add(const SensorData_t& data);

    size_t getCount() const;

    // 输出 JSON 数组(时间序: 最旧→最新), limit 限制条数
    // [{"ts":1723..,"t":28.9,"h":64.4,"s":30}, ...]
    String toJson(size_t limit = MAX_POINTS) const;
};

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_HISTORY_SERVICE_H
