#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int lnk_search(LinkList L, int k, ElemType* p_ele) {
    Node* fast=L->next;
    Node* slow=L->next;
    int count=k-1;
    while (fast != NULL) {
        if (count!=0) {
            count--;
            fast=fast->next;
        }else {
            slow=slow->next;
            fast=fast->next;
        }
    }
    if (count!=0) {
        return 0;
    }
    *p_ele=slow->data;
    return 1;
}