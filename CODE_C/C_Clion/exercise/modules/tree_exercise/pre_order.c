#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过

void visit_node(BiTNode *node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
}

void pre_order(BiTree root){
    if(root==NULL) {
        return;
    }
    Stack S;
    init_stack(&S);
    push(&S,root);
    BiTree curr;
    while(!is_empty(&S)) {
        pop(&S,&curr);
        visit_node(curr);
        if (curr->right != NULL) {
            push(&S,curr->right);
        }
        if (curr->left != NULL) {
            push(&S,curr->left);
        }
    }
}
