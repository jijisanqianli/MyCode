#ifndef LIST_H
#define LIST_H

#define MAXSIZE 100  // 顺序表最大容量
typedef int ElemType; // 数据元素类型为int

// 顺序表结构体定义
struct _seqlist {
    ElemType elem[MAXSIZE]; // 存储元素的数组
    int last;               // 最后一个元素的下标，表长 = last + 1
};
typedef struct _seqlist SeqList;

void odd_even(SeqList *L);
void exchange(int* a,int* b);
void print_list(SeqList *L);
void odd_evenPlus(SeqList *L);
void del_dupnum(SeqList *L);
void del_dupnumPlus(SeqList *L);
void del_x2y(SeqList *L, ElemType x, ElemType y);
SeqList* createSeqList();
void setSeqList(SeqList* L, int index);

#endif