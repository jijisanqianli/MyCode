#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void lnk_del_x2y(LinkList L, ElemType mink, ElemType maxk) {
    Node* tail= L->next;
    Node* begin=NULL;
    Node* end=NULL;
    Node* last_node=L;
    int get_min=0;
    while (tail != NULL) {
        //printf("循环开始时的节点值为%d\n",tail->data);
        if (tail->data > mink && get_min==0) {
            begin = last_node;
            begin->next = NULL;
            get_min = 1;
         }
        if (tail->data >= maxk) {
            end = tail;
            //printf("在%d处退出\n",tail->data);
            break;
        }
        Node* storage=tail->next;
        last_node=tail;
        if (get_min==1) {
            free(tail);
        }
        tail = storage;
        //printf("循环完成一次\n");
        //printf("循环结束时的节点值为%d\n",tail->data);
    }
    //printf("此时的节点值为%d\n",tail->data);
    begin->next = end;
}