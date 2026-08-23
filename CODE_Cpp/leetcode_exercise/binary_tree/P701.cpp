#include "binary_tree.h"

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root==nullptr) return new TreeNode(val);
        TreeNode* cur=root;
        while (true) {
            if (cur->val>val) {
                if (cur->left==nullptr) {
                    cur->left=new TreeNode(val);
                    break;
                }
                cur=cur->left;
            }else {
                if (cur->right==nullptr) {
                    cur->right=new TreeNode(val);
                    break;
                }
                cur=cur->right;
            }
        }
        return root;
    }
};
