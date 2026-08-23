#include "binary_tree.h"

class Solution {
    TreeNode* buildTree(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = left+right >> 1;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = buildTree(nums, left, mid-1);
        root->right = buildTree(nums, mid+1, right);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildTree(nums, 0, nums.size()-1);
    }

    TreeNode* sortedArrayToBSTInterative(vector<int>& nums) {
        queue<int> leftQue, rightQue;
        queue<TreeNode*> nodeQue;
        TreeNode* root = new TreeNode(0);
        nodeQue.push(root);
        leftQue.push(0);
        rightQue.push(nums.size()-1);
        while (!nodeQue.empty()) {
            TreeNode* node = nodeQue.front(); nodeQue.pop();
            int left = leftQue.front(); leftQue.pop();
            int right = rightQue.front(); rightQue.pop();
            int mid = left+right >> 1;
            node->val = nums[mid];
            if (left <= mid-1) {
                node->left = new TreeNode(0);
                nodeQue.push(node->left);
                leftQue.push(left);
                rightQue.push(mid-1);
            }
            if (right >= mid+1) {
                node->right = new TreeNode(0);
                nodeQue.push(node->right);
                leftQue.push(mid+1);
                rightQue.push(right);
            }
        }
        return root;
    }
};