#include "seqlist.h"
#include <stdio.h>
#include <stdlib.h>

// 1. 创建空顺序表
SeqList* createSeqList() {
    SeqList* list = (SeqList*)malloc(sizeof(SeqList));
    if (list == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    // 空表：最后一个元素下标为-1
    list->last = -1;
    return list;
}

// 2. 手动输入数据
void inputSeqList(SeqList* list) {
    int n;
    printf("请输入要输入的元素个数：");
    scanf("%d", &n);
    if (n <= 0 || n > MAXSIZE) {
        printf("输入个数非法！\n");
        return;
    }
    printf("请输入%d个整数（空格分隔）：", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &list->elem[i]);
    }
    // 更新最后一个元素下标
    list->last = n - 1;
}

// 3. 插入元素（i是插入位置下标，从0开始）
int insertSeqList(SeqList* list, int i, ElemType x) {
    // 检查顺序表是否满
    if (list->last == MAXSIZE - 1) {
        printf("顺序表已满，无法插入！\n");
        return 0; // 插入失败
    }
    // 检查插入位置是否合法
    if (i < 0 || i > list->last + 1) {
        printf("插入位置非法！\n");
        return 0;
    }
    // 从后往前移动元素，腾出位置
    for (int j = list->last; j >= i; j--) {
        list->elem[j + 1] = list->elem[j];
    }
    // 插入新元素
    list->elem[i] = x;
    // 最后一个元素下标+1
    list->last++;
    return 1; // 插入成功
}

// 4. 查找元素
int searchSeqList(SeqList* list, ElemType x) {
    for (int i = 0; i <= list->last; i++) {
        if (list->elem[i] == x) {
            // 找到，返回下标
            return i;
        }
    }
    // 没找到
    return -1;
}

// 5. 删除元素
int deleteSeqList(SeqList* list, int i) {
    // 检查顺序表是否空
    if (list->last == -1) {
        printf("顺序表为空，无法删除！\n");
        return 0;
    }
    // 检查删除位置是否合法
    if (i < 0 || i > list->last) {
        printf("删除位置非法！\n");
        return 0;
    }
    // 从前往后移动元素，覆盖被删除的位置
    for (int j = i; j < list->last; j++) {
        list->elem[j] = list->elem[j + 1];
    }
    // 最后一个元素下标-1
    list->last--;
    return 1; // 删除成功
}

// 6. 修改元素
int updateSeqList(SeqList* list, int i, ElemType x) {
    if (list->last == -1) {
        printf("顺序表为空！\n");
        return 0;
    }
    if (i < 0 || i > list->last) {
        printf("修改位置非法！\n");
        return 0;
    }
    list->elem[i] = x;
    return 1; // 修改成功
}

// 7. 打印顺序表
void printSeqList(SeqList* list) {
    if (list->last == -1) {
        printf("顺序表为空！\n");
        return;
    }
    printf("顺序表元素：");
    for (int i = 0; i <= list->last; i++) {
        printf("%d ", list->elem[i]);
    }
    printf("\n");
}

// 8. 销毁顺序表（释放内存）
void destroySeqList(SeqList* list) {
    free(list);
    list = NULL; // 避免野指针
    printf("顺序表已销毁！\n");
}