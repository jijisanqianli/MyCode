#include <stdlib.h>
#include <stdio.h>
#include "bitree.h"

bool path(BiTNode* root, BiTNode* node, Stack* s) {
    if (root == NULL) return false;
    push(s, root);
    if (root == node) return true;
    if (root->left!=NULL) {
        if (path(root->left, node, s)) return true;
    }
    if (root->right!=NULL) {
        if (path(root->right, node, s)) return true;
    }
    ElemType temp;
    pop(s, &temp);
    return false;
}

#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过

bool path_plus(BiTNode* root, BiTNode* node, Stack* s) {
    if (root == NULL || node == NULL) return false;

    BiTNode* p = root;
    BiTNode* r = NULL; // 用来记录最近访问过的节点
    ElemType temp;

    while (p != NULL || !is_empty(s)) {
        if (p != NULL) {
            push(s, p); // 沿左子树一直向下，顺便把路径上的节点入栈
            if (p == node) {
                return true; // 刚好找到了目标节点！此时栈内 root 在栈底，node 在栈顶，完美符合！
            }
            p = p->left;
        } else {
            top(s, &p); // 读栈顶节点，但不弹出
            // 如果右子树存在，且未被访问过，则转向右子树
            if (p->right != NULL && p->right != r) {
                p = p->right;
            } else {
                // 否则，说明左右子树都访问完了，弹出该节点
                pop(s, &temp);
                r = p; // 记录最近访问过的节点
                p = NULL; // 节点访问完后，重置 p 使得下次继续取栈顶
            }
        }
    }
    return false;
}
