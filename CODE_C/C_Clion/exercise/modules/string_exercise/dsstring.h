#ifndef EXERCISE_DSSTRING_H
#define EXERCISE_DSSTRING_H

#define BLOCK_SIZE 4    // 可由用户定义的块大小
#define BLS_BLANK '#'   // 用于空白处的补齐字符

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _block {
    char ch[BLOCK_SIZE];    //块的数据域
    struct _block *next;    //块的指针域
} Block;

typedef struct {
    Block *head;        // 串的头指针
    Block *tail;        // 串的尾指针
    int len;            // 串的当前长度
} BLString;

//字符串初始化函数：
void blstr_init(BLString *T) {
    T->len = 0;
    T->head = NULL;
    T->tail = NULL;
}

#endif //EXERCISE_DSSTRING_H