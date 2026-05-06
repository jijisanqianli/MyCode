#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "bitree.h"

// 初始化栈：将栈顶指针置为 -1，表示栈为空
void init_stack(Stack *S) {
    S->top = -1;
}

// 检查栈是否为空
bool is_empty(Stack* S) {
    return S->top == -1;
}

// 入栈操作
bool push(Stack* S, ElemType x) {
    // 检查栈是否已满
    if (S->top == Stack_Size - 1) {
        return false;
    }
    // top 先自增，再存入元素
    S->elem[++(S->top)] = x;
    return true;
}

// 出栈操作：将元素保存到 px 指向的地址
bool pop(Stack* S, ElemType *px) {
    // 检查栈是否为空
    if (is_empty(S)) {
        return false;
    }
    // 先取出元素，top 再自减
    *px = S->elem[(S->top)--];
    return true;
}

// 获取栈顶元素（不出栈）
bool top(Stack* S, ElemType *px) {
    if (is_empty(S)) {
        return false;
    }
    *px = S->elem[S->top];
    return true;
}
