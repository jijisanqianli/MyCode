#include <stdlib.h>
#include <stdio.h>
#include "bitree.h"

typedef struct{
    CSNode* source;
    BiTNode* brother;
    CSNode* father;
}brother_node;

void cope(BiTNode* Bi_begin,CSNode* CS_begin,Queue* my_queue,CSNode* history) {
    CSNode* pre=history;CSNode* CS_now=CS_begin;BiTNode* Bi_now=Bi_begin;
    while (CS_now!=NULL) {
        if (CS_now->children[0]!=NULL) {
            BiTNode *son = (BiTNode *)malloc(sizeof(BiTNode));
            son->data=CS_now->children[0]->data;son->right=NULL;son->left=NULL;
            Bi_now->left=son;
        }
        if (pre!=NULL) {
            int i=0;
            while (i < MAX_CHILDREN_NUM && pre->children[i] != CS_now) {
                i++;
            }
            if (i < MAX_CHILDREN_NUM && i + 1 < MAX_CHILDREN_NUM) {
                if (pre->children[i+1]!=NULL) {
                    BiTNode *brother = (BiTNode *)malloc(sizeof(BiTNode));
                    brother->data=pre->children[i+1]->data;brother->right=NULL;brother->left=NULL;
                    Bi_now->right=brother;
                    brother_node* node=malloc(sizeof(brother_node));
                    node->brother=brother;node->father=pre;node->source=pre->children[i+1];
                    add_queue(my_queue,node);
                }
            }
        }
        pre=CS_now;
        CS_now=CS_now->children[0];Bi_now=Bi_now->left;
    }
    if (is_empty_queue(my_queue)) {
        return;
    }
    brother_node* next_begin=del_queue(my_queue);
    cope(next_begin->brother,next_begin->source,my_queue,next_begin->father);
}



BiTNode* transform(CSNode *root){
    if (root == NULL) {
        return NULL;
    }
    Queue* my_queue=create_queue();
    BiTNode* Bi_root=malloc(sizeof(BiTNode));
    Bi_root->data=root->data;Bi_root->left=NULL;Bi_root->right=NULL;
    cope(Bi_root,root,my_queue,NULL);
    return Bi_root;
}