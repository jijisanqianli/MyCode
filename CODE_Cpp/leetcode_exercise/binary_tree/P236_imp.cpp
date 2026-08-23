#include "binary_tree.h"

class Solution {
    bool hasNode(TreeNode* root, TreeNode*& p, TreeNode*& q, TreeNode*& res) {
        if (res) return true;
        if (!root) return false;
        bool self = (root == p || root == q);
        bool left = hasNode(root->left, p, q, res);
        if (res) return true;
        bool hasTwo = (self + left) >= 2;
        if (hasTwo) {
            res = root;
            return true;
        }
        bool right = hasNode(root->right, p, q, res);
        hasTwo = (self + left + right) >= 2;
        if (hasTwo) res = root;
        return self || left || right;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* res = nullptr;
        hasNode(root, p, q, res);
        return res;
    }

    class Solution {
    public:
        TreeNode* lowestCommonAncestorBest(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (!root || root == p || root == q) return root; // (1) 提前返回
            TreeNode* left = lowestCommonAncestorBest(root->left, p, q);
            TreeNode* right = lowestCommonAncestorBest(root->right, p, q);
            if (left && right) return root;
            return left ? left : right;
        }
    };
};
