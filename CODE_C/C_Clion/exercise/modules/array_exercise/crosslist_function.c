#include <stdio.h>
#include <stdlib.h>
#include "crosslist.h"

int init_cross_list(PCrossList L, const ElemType *A, int m,int n){
    L->rows=m;L->cols=n;
    int nums=0,countA=0;
    L->rowhead = (OLink*)malloc(m * sizeof(OLink));
    L->colhead = (OLink*)malloc(n * sizeof(OLink));
    OLNode** last_right=NULL;OLNode** last_down[n];
    for (int i=0;i<m;i++) L->rowhead[i]=NULL;
    for (int i=0;i<n;i++) {
        L->colhead[i]=NULL;
        last_down[i]=&L->colhead[i];
    }
    for(int i=0;i<m;i++) {
        last_right=&L->rowhead[i];
        for(int j=0;j<n;j++) {
            if (A[countA]!=0) {
                //创建新节点
                OLNode* newNode=(OLNode*)malloc(sizeof(OLNode));
                //补充上一个节点的内部结构
                *last_right=newNode;
                *last_down[j]=newNode;
                   //row,col不指代下标,i,j指代下标
                newNode->row=i+1;newNode->col=j+1;newNode->value=A[countA];
                newNode->right=NULL;newNode->down=NULL;
                last_right=&newNode->right;last_down[j]=&newNode->down;
                nums++;
            }
            countA++;
        }
    }
    L->nums=nums;
    return nums;
}

int del_cross_list(PCrossList L, ElemType k) {
    int count=0;
    for (int i=0;i<L->rows;i++) {
        if (L->rowhead[i]!=NULL) {
            OLNode** row_curr = &L->rowhead[i];
            while (*row_curr!=NULL) {
                OLNode* now=*row_curr;
                if (now->value==k) {
                    count++;
                    *row_curr=now->right;
                    OLNode** col_curr=&L->colhead[now->col-1];
                    while (*col_curr!=now) {
                        col_curr=&(*col_curr)->down;
                    }
                    *col_curr=now->down;
                    free(now);
                    continue;
                }
                row_curr=&(*row_curr)->right;
            }
        }
    }
    L->nums-=count;
    return count;
}

int del_cross_list_initial(PCrossList L, ElemType k){
    int count = 0;
    for (int i = 0; i < L->rows; i++) {
        // --- 第一阶段：处理行头连续是 k 的情况 ---
        // 只要行头不为空且值等于 k，就一直删头
        while (L->rowhead[i] != NULL && L->rowhead[i]->value == k) {
            OLNode* trash = L->rowhead[i];

            // 纵向清理（必须在 free 之前）
            OLNode** col_curr = &L->colhead[trash->col - 1];
            while (*col_curr != trash) {
                col_curr = &((*col_curr)->down);
            }
            *col_curr = trash->down;

            // 横向断开：行头移向下一个
            L->rowhead[i] = trash->right;
            free(trash);
            count++;
        }

        // --- 第二阶段：处理行中间的 k ---
        // 此时能保证行头要么是 NULL，要么值不是 k
        if (L->rowhead[i] != NULL) {
            OLNode* prev = L->rowhead[i];
            OLNode* curr = prev->right;

            while (curr != NULL) {
                if (curr->value == k) {
                    OLNode* trash = curr;

                    // 纵向清理
                    OLNode** col_curr = &L->colhead[trash->col - 1];
                    while (*col_curr != trash) {
                        col_curr = &((*col_curr)->down);
                    }
                    *col_curr = trash->down;

                    // 横向断开：前驱跳过当前节点
                    prev->right = trash->right;

                    // 关键：curr 移向下一个，但 prev 不动！
                    curr = prev->right;
                    free(trash);
                    count++;
                } else {
                    // 没删，两个指针才一起往后走
                    prev = curr;
                    curr = curr->right;
                }
            }
        }
    }
    L->nums -= count;
    return count;
}