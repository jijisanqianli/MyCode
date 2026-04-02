#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void del_x2y(SeqList *L, ElemType x, ElemType y) {
    int real_location=-1;//慢指针，指向实际位置
    int now_location=0;//遍历整个表
    while (now_location<=L->last) {
        //不在范围内
        if (L->elem[now_location]<x || L->elem[now_location]>y) {
            real_location++;
            L->elem[real_location]=L->elem[now_location];
        }
        now_location++;
    }
    L->last=real_location;
}