#include <stdlib.h>
#include <stdio.h>
#include "bitree.h"

BiTNode * nearest_ancestor(BiTree root, BiTNode *p, BiTNode *q){
    Stack sp,sq;
    init_stack(&sp);init_stack(&sq);
    path(root,p,&sp);
    path(root,q,&sq);
    for (int i=sp.top;i>=0;i--) {
        BiTNode* now = sp.elem[i];
        for (int j=sq.top;j>=0;j--) {
            BiTNode* temp = sq.elem[j];
            if (temp==now) return temp;
        }
    }
    return NULL;
}