#ifndef SEQLIST_H_
#define SEQLIST_H_

// 最大容量
#define MAXSIZE 100
// 数据类型（可按需改成char/long等）
typedef int ElemType;

// 顺序表结构体定义
typedef struct {
    // 存储数据的数组
    ElemType elem[MAXSIZE];
    // 最后一个元素的下标（空表为-1）
    int last;
} SeqList;

// 函数声明（核心操作）
// 1. 创建空顺序表（动态分配内存）
SeqList* createSeqList();
// 2. 手动输入数据到顺序表
void inputSeqList(SeqList* list);
// 3. 插入元素：在第i个位置（从0开始）插入x
int insertSeqList(SeqList* list, int i, ElemType x);
// 4. 查找元素：返回第一个x的下标，没找到返回-1
int searchSeqList(SeqList* list, ElemType x);
// 5. 删除元素：删除第i个位置的元素
int deleteSeqList(SeqList* list, int i);
// 6. 修改元素：把第i个位置的元素改成x
int updateSeqList(SeqList* list, int i, ElemType x);
// 7. 打印顺序表所有元素（辅助测试）
void printSeqList(SeqList* list);
// 8. 销毁顺序表（释放内存）
void destroySeqList(SeqList* list);

#endif // SEQLIST_H_