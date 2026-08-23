#include "binary_tree.h"

class Solution {
public:
    int findMaxIndex(vector<int>& nums, int left, int right) {
        int max = INT_MIN;
        int maxIndex = left;
        for (int i = left; i <= right; i++) {
            if (nums[i] > max) {
                max=nums[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    TreeNode* build(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int maxIndex = findMaxIndex(nums, left, right);
        TreeNode* root = new TreeNode(nums[maxIndex]);
        root->left = build(nums, left, maxIndex - 1);
        root->right = build(nums, maxIndex + 1, right);
        return root;
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return build(nums, 0, nums.size() - 1);
    }

    TreeNode* constructMaximumBinaryTreeBest(vector<int>& nums) {
        vector<TreeNode*> stack;
        for (int i = 0; i < nums.size(); i++) {
            TreeNode* cur = new TreeNode(nums[i]);
            while (!stack.empty() && stack.back()->val < nums[i]) {
                cur->left = stack.back();
                stack.pop_back();
            }
            if (stack.empty()) {
                stack.push_back(cur);
            }else {
                stack.back()->right = cur;
                stack.push_back(cur);
            }
        }
        return stack.front();
    }
};
