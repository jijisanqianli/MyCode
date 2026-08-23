#ifndef EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_CONTROLTASK_H
#define EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_CONTROLTASK_H

// controlTask: 核1 优先级3, 队列集阻塞等待 manualIrrQueue(手动指令) 与 autoIrrQueue(自动灌溉触发),
// 模式状态机: AUTO(自动灌溉) / MANUAL(手动指令), pump 指令自动切 MANUAL
// 参数: IrrigationService*
void controlTask(void* param);

#endif //EMBEDDED_SYSTEM_SUMMER_RECRUITMENT_CONTROLTASK_H
