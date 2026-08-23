#include "binary_tree.h"

class Solution {
public:
    bool visit(TreeNode* root, int targetSum, vector<int>& sums) {
        sums.push_back(root->val);
        if (!root->left && !root->right) {
            int sum = 0;
            for (int i = 0; i < sums.size(); i++) {
                sum += sums[i];
            }
            sums.pop_back();
            if (sum == targetSum) return true;
            return false;
        }
        if (root->left && !root->right) {
            bool res = visit(root->left, targetSum, sums);
            sums.pop_back();
            return res;
        }
        if (root->right && !root->left) {
            bool res = visit(root->right, targetSum, sums);
            sums.pop_back();
            return res;
        }
        bool res = visit(root->left, targetSum, sums) || visit(root->right, targetSum, sums);
        sums.pop_back();
        return res;
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        vector<int> sums;
        return visit(root, targetSum, sums);
    }

    bool visitBest(TreeNode* root, int targetSum, int sum) {
        if (!root) return false;
        sum += root->val;
        if (!root->left && !root->right) {
            return sum == targetSum;
        }
        return visitBest(root->left, targetSum, sum) || visitBest(root->right, targetSum, sum);
    }

    bool hasPathSumBest(TreeNode* root, int targetSum) {
        if (!root) return false;
        return visitBest(root, targetSum, 0);
    }
};