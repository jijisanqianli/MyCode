#include "binary_tree.h"

class Solution {
public:
    int height(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(height(root->left), height(root->right)) + 1;
    }

    bool isBalanced0(TreeNode* root) {
        if (root == nullptr) return true;
        return abs(height(root->left) - height(root->right)) <= 1 && isBalanced0(root->left) && isBalanced0(root->right);
    }

    int checkHeight(TreeNode* root) {
        if (root == nullptr) return 0;
        int left = checkHeight(root->left);
        if (left == -1) return -1;
        int right = checkHeight(root->right);
        if (right == -1) return -1;
        if (abs(left - right) > 1) return -1;
        return max(left, right) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }
};