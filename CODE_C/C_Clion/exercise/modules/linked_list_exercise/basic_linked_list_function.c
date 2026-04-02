#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* create_node(ElemType data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("\nMemory allocation failed");
    }else {
        node -> next = NULL;
        node -> data = data;
    }
    return node;
}

void add_new_node(Node* head,ElemType data) {
    Node* tail= head;
    while (tail->next != NULL) {
        tail = tail -> next;
    }
    Node* new_node = create_node(data);
    new_node -> next = NULL;
    new_node -> data = data;
    tail -> next = new_node;
}

void printList(Node* head) {
    Node* tail=head;
    while (tail->next != NULL) {
        printf("%d ", tail -> data);
        tail = tail -> next;
    }
    printf("%d\n", tail -> data);
}