#include <stdio.h>
#include <stdlib.h>
#include "list.h"
//我的代码
void del_dupnum(SeqList *L) {
    if (L == NULL || L->last <= 0) return;
    int count=1;//有多少个不同数字
    for (int i=0;i<=(L->last)-1;i++) {
        if (L->elem[i]!=L->elem[i+1]) {
            count++;
            L->elem[count-1]=L->elem[i+1];
        }
    }
    L->last=count-1;
}

//ai的代码
void del_dupnumPlus(SeqList *L) {
    if (L == NULL || L->last <= 0) return;
    int real_location=0;//慢指针，指向实际位置
    int now_location=1;//遍历整个表
    while (now_location<=L->last) {
        if (L->elem[now_location]!=L->elem[real_location]) {
            real_location++;
            L->elem[real_location]=L->elem[now_location];
        }
        now_location++;
    }
    L->last=real_location;
}