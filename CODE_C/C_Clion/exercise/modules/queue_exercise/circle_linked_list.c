#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

bool init_queue(LinkQueue *LQ) {
    LinkQueueNode* head=(LinkQueueNode*)malloc(sizeof(LinkQueueNode));
    if (head==NULL) {
        return false;
    }
    head->next=head;
    *LQ=head;
    return true;
}

bool enter_queue(LinkQueue *LQ, ElemType x) {
    LinkQueueNode* last=(LinkQueueNode*)malloc(sizeof(LinkQueueNode));
    if (last==NULL) {
        return false;
    }
    last->data=x;
    last->next=(*LQ)->next;
    (*LQ)->next=last;
    *LQ=last;
    return true;
}

bool leave_queue(LinkQueue *LQ, ElemType *x) {
    if ((*LQ)->next==NULL||(*LQ)->next==*LQ) {
        return false;
    }
    LinkQueueNode* the_delete=(*LQ)->next->next;
    *x=the_delete->data;
    (*LQ)->next->next=the_delete->next;
    if (the_delete==*LQ) {
        *LQ=(*LQ)->next;
    }
    free(the_delete);
    return true;
}

void print_queue(LinkQueue *LQ) {
    if ((*LQ)->next==NULL||(*LQ)->next==*LQ) {
        return;
    }
    LinkQueueNode* tail=(*LQ)->next->next;
    while (tail!=*LQ) {
        printf("%d ",tail->data);
        tail=tail->next;
    }
    printf("%d",tail->data);
}