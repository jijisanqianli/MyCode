#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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

void setSeqList(SeqList* L, int index) {
    L->last=index-1;
    for (int i= 0; i <= L->last; i++) {
        scanf("%d",&L->elem[i]);
    }
}