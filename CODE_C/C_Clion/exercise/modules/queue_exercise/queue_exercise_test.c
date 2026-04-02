#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

int main() {
    char* str="9 3 1 - 3 * + 10 2 / +";
    print_str(str);
    printf("\n");
    printf("计算结果为:%d",compute_reverse_polish_notation(str));
    return 0;
    /*LinkQueue queue;
    ElemType x;
    init_queue(&queue);
    enter_queue(&queue,1);
    enter_queue(&queue,2);
    print_queue(&queue);
    printf("\n");
    enter_queue(&queue,3);
    enter_queue(&queue,4);
    print_queue(&queue);
    printf("\n");
    leave_queue(&queue,&x);
    printf("删除的数据是:%d\n",x);
    print_queue(&queue);
    printf("\n");
    leave_queue(&queue,&x);
    printf("删除的数据是:%d\n",x);
    print_queue(&queue);
    return 0;*/
}