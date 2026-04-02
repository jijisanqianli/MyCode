#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void init_stack(Stack *S){
    S->top = -1;
}

bool is_empty(Stack *S) {
    return S->top == -1;
}

bool is_full(Stack *S) {
    return S->top == Stack_Size - 1;
}

bool push(Stack* S, ElemType x) {
    if(is_full(S)) {
        printf("Stack is full\n");
        return false;
    }
    S->top++;
    S->elem[S->top] = x;
    return true;
}

bool pop(Stack* S, ElemType *x) {
    if(is_empty(S)) {
        printf("Stack is empty\n");
        return false;
    }
    *x = S->elem[S->top];
    S->top--;
    return true;
}