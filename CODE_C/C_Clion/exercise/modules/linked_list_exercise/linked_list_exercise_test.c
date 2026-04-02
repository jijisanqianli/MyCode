#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* create_list_A() {
    Node* a1 = (Node*)malloc(sizeof(Node));
    Node* a2 = (Node*)malloc(sizeof(Node));
    Node* a3 = (Node*)malloc(sizeof(Node));

    a1->data = 1;
    a1->next = a2;

    a2->data = 3;
    a2->next = a3;

    a3->data = 5;
    a3->next = NULL;

    return a1;
}

// 手动创建链表B: 2 → 4 → 6 → 8 → NULL (n=4)
Node* create_list_B() {
    Node* b1 = (Node*)malloc(sizeof(Node));
    Node* b2 = (Node*)malloc(sizeof(Node));
    Node* b3 = (Node*)malloc(sizeof(Node));
    Node* b4 = (Node*)malloc(sizeof(Node));

    b1->data = 2;
    b1->next = b2;

    b2->data = 4;
    b2->next = b3;

    b3->data = 6;
    b3->next = b4;

    b4->data = 8;
    b4->next = NULL;

    return b1;
}

LinkList create_header() {
    Node *h = (Node*)malloc(sizeof(Node));
    h->next = NULL;
    h->data = -1;  // 头结点数据无效
    return h;
}

LinkList create_test1_A() {
    Node* a1 = (Node*)malloc(sizeof(Node));
    Node* a2 = (Node*)malloc(sizeof(Node));
    Node* a3 = (Node*)malloc(sizeof(Node));
    a1->data = 1; a1->next = a2;
    a2->data = 3; a2->next = a3;
    a3->data = 5; a3->next = NULL;
    return a1;
}

LinkList create_test1_B() {
    Node* b1 = (Node*)malloc(sizeof(Node));
    Node* b2 = (Node*)malloc(sizeof(Node));
    Node* b3 = (Node*)malloc(sizeof(Node));
    Node* b4 = (Node*)malloc(sizeof(Node));
    Node* b5 = (Node*)malloc(sizeof(Node));
    b1->data = 2; b1->next = b2;
    b2->data = 4; b2->next = b3;
    b3->data = 6; b3->next = b4;
    b4->data = 8; b4->next = b5;
    b5->data = 10; b5->next = NULL;
    return b1;
}

LinkList create_test2_A() {
    Node* a0 = (Node*)malloc(sizeof(Node));
    Node* a1 = (Node*)malloc(sizeof(Node));
    Node* a2 = (Node*)malloc(sizeof(Node));
    Node* a3 = (Node*)malloc(sizeof(Node));
    Node* a4 = (Node*)malloc(sizeof(Node));
    Node* a5 = (Node*)malloc(sizeof(Node));
    Node* a6 = (Node*)malloc(sizeof(Node));
    a0->next = a1;
    a1->data = 1; a1->next = a2;
    a2->data = 3; a2->next = a3;
    a3->data = 5; a3->next = a4;
    a4->data = 7; a4->next = a5;
    a5->data = 9; a5->next = a6;
    a6->data = 11; a6->next = NULL;
    return a0;
}

LinkList create_test2_B() {
    Node* b0 = (Node*)malloc(sizeof(Node));
    Node* b1 = (Node*)malloc(sizeof(Node));
    Node* b2 = (Node*)malloc(sizeof(Node));
    Node* b3 = (Node*)malloc(sizeof(Node));
    b0->next=b1;
    b1->data = 2; b1->next = b2;
    b2->data = 4; b2->next = b3;
    b3->data = 6; b3->next = NULL;
    return b0;
}

int main() {
    LinkList A = create_test2_A();
    printList(A);
    lnk_del_x2y(A,4,10);
    printList(A);
    return 0;
}