#include "binary_tree.h"

class Solution {
public:
    int countNodes(TreeNode* root) {
        int l=0,r=0;
        TreeNode* left=root;
        TreeNode* right=root;
        while(left) {
            l++;
            left=left->left;
        }
        while(right) {
            r++;
            right=right->right;
        }
        if(l==r) return (1<<l)-1;
        return countNodes(root->left)+countNodes(root->right)+1;
    }
};