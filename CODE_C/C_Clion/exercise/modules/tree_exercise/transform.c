#include <stdlib.h>
#include <stdio.h>
#include "bitree.h"

typedef struct {
    BiTNode* Bi;
    CSNode* CS;
}Package;

BiTNode* transform(CSNode *root) {
    if (root == NULL) return NULL;
    Queue* my_queue=create_queue();
    BiTNode* Bi_root=malloc(sizeof(BiTNode));
    Bi_root->data=root->data;
    Bi_root->left=NULL;Bi_root->right=NULL;
    Package* begin=malloc(sizeof(Package));begin->Bi=Bi_root;begin->CS=root;
    add_queue(my_queue,begin);
    while (!is_empty_queue(my_queue)) {
        Package* now=del_queue(my_queue);
        BiTNode* Bi_now=now->Bi;CSNode* CS_now=now->CS;BiTNode* pre=NULL;
        for (int i=0;i<MAX_CHILDREN_NUM&&CS_now->children[i]!=NULL;i++) {
            BiTNode* son=malloc(sizeof(BiTNode));
            son->data=CS_now->children[i]->data;
            son->left=NULL;son->right=NULL;
            if (i==0) {
                Bi_now->left=son;
            }
            if (pre!=NULL) {
                pre->right=son;
            }
            Package* new_package=malloc(sizeof(Package));
            new_package->Bi=son;new_package->CS=CS_now->children[i];
            add_queue(my_queue,new_package);
            pre=son;
        }
        free(now);
    }
    free_queue(my_queue);
    return Bi_root;
}