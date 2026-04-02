#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//我自己的做法
void odd_even(SeqList *L) {
    int left=L->last;
    int end=0;
    for (int i=0;i<=L->last;i++) {
        if (L->elem[i]%2==0) {
            if (left<=i) {
                //printf("一");
                break;
            }
            int have_odd=0;
            for (int j=left;j>=i;j--) {
                if ((L->elem[j])%2!=0) {
                    exchange(&(L->elem[i]),&(L->elem[j]));
                    //printf("%d,%d\n",L->elem[i],L->elem[j]);
                    left=j;
                    have_odd=1;
                    break;
                }
            }
            if (have_odd!=1) {
                //printf("二");
                break;
            }
        }
    }
}

void odd_evenPlus(SeqList *L) {
    // 边界检查
    if (L == NULL || L->last < 0) return;

    int left = 0;           // 左指针，指向开头
    int right = L->last;    // 右指针，指向结尾

    while (left < right) {
        // 左指针向右移动，直到找到一个偶数
        while (left < right && L->elem[left] % 2 != 0) {
            left++;
        }

        // 右指针向左移动，直到找到一个奇数
        while (left < right && L->elem[right] % 2 == 0) {
            right--;
        }

        // 如果找到了一对（左边是偶数，右边是奇数），交换它们
        if (left < right) {
            int temp = L->elem[left];
            L->elem[left] = L->elem[right];
            L->elem[right] = temp;

            // 交换后指针继续移动
            left++;
            right--;
        }
    }
}

void exchange(int* a,int* b) {
    int middle=*a;
    *a=*b;
    *b=middle;
}

void print_list(SeqList *L) {
    for (int i=0;i<=L->last;i++) {
        printf("%d ",L->elem[i]);
    }
}
