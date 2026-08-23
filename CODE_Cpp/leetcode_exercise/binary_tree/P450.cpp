#include "binary_tree.h"

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        while (cur != nullptr && cur->val != key) {
            pre = cur;
            if (key < cur->val) cur = cur->left;
            else cur = cur->right;
        }
        if (cur == nullptr) return root;
        if (cur->left == nullptr && cur->right == nullptr) {
            if (pre == nullptr) root=nullptr;
            else if (pre->left == cur) pre->left = nullptr;
            else pre->right = nullptr;
        }
        else if (cur->left == nullptr) {
            if (pre == nullptr) {
                root = cur->right;
            }
            else if (pre->left == cur) pre->left = cur->right;
            else pre->right = cur->right;
        }else if (cur->right == nullptr) {
            if (pre == nullptr) {
                root = cur->left;
            }
            else if (pre->left == cur) pre->left = cur->left;
            else pre->right = cur->left;
        }else {
            TreeNode* temp = cur->right;
            while (temp->left != nullptr) temp = temp->left;
            temp->left = cur->left;
            if (pre == nullptr) {
                root = cur->right;
            }
            else if (pre->left == cur) pre->left = cur->right;
            else pre->right = cur->right;
        }
        delete cur;
        return root;
    }
};