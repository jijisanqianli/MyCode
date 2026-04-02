#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void lnk_merge(LinkList A, LinkList B, LinkList C) {
    Node* tail_A=A;
    Node* tail_B=B;
    while (tail_A!=NULL && tail_B!=NULL) {
        C->next=tail_A;
        C=C->next;
        tail_A=tail_A->next;

        C->next=tail_B;
        C=C->next;
        tail_B=tail_B->next;
    }
    if (tail_A==NULL&&tail_B!=NULL) {
        C->next=tail_B;
    }
    if (tail_B==NULL&&tail_A!=NULL) {
        C->next=tail_A;
    }
}

void lnk_merge_failed(LinkList A, LinkList B, LinkList C) {
    Node* tail_A=A;
    Node* tail_B=B;
    Node* tail_C=C;
    //保存指向下一个a的指针
    Node* next_A=tail_A->next;
    Node* next_B;
    while (tail_A->next!=NULL && tail_B->next!=NULL) {
        //连接下一个b节点
        tail_C->next=tail_B;
        //进入b节点
        tail_C=tail_C->next;
        //保存指向下一个b节点的指针
        next_B=tail_C->next;
        printf("%d\n",tail_C->data);
        //a节点递进
        tail_A=next_A;
        //连接下一个a节点
        tail_C->next=tail_A;
        //进入a节点
        tail_C=tail_C->next;
        printf("%d\n",tail_C->data);
        //保存指向下一个a的指针
        next_A=tail_C->next;
        //b节点递进
        tail_B=next_B;
        /*printList(tail_A);
        printList(tail_B);*/
        printf("完整执行了一次\n");
        printList(C);
    }
    printf("循环已结束\n");
    if (tail_A->next==NULL&&tail_B->next!=NULL) {
        printf("进入1\n");
        tail_C->next=tail_B;
        printf("1结束\n");
    }
    if (tail_A->next!=NULL&&tail_B->next==NULL) {
        printf("进入2");
        tail_C->next=tail_A->next;
    }
    printf("函数结束\n");
}



