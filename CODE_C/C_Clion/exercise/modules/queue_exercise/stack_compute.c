#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

int compute_reverse_polish_notation(char *str){
    Stack* S=(Stack*)malloc(sizeof(Stack));
    init_stack(S);
    int num=0;
    bool last_if_num=true;
    while (*str != '\0') {
        if (*str>='0' && *str<='9') {
            num=num*10+(*str-'0');
            last_if_num=true;
        }
        if (*str == ' '&&last_if_num) {
            //printf("压入数字:%d\n",num);
            push(S,num);
            num=0;
        }
        if (*str == '+'||*str == '-'||*str == '*'||*str == '/'||*str == '%') {
            int num1,num2;
            pop(S,&num1);
            pop(S,&num2);
            if (*str=='*') {
                push(S,num2*num1);
            }else if (*str=='/') {
                push(S,num2/num1);
            }else if (*str=='+') {
                push(S,num2+num1);
            }else if (*str=='-') {
                push(S,num2-num1);
            }else if (*str=='%') {
                push(S,num2%num1);
            }
            last_if_num=false;
        }
        str++;
    }
    int result;
    pop(S,&result);
    return result;
}

void print_str(char *str) {
    while (*str != '\0') {
        if (*str != ' ') {
            printf("%c", *str);
        }
        str++;
    }
}