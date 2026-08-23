#include "binary_tree.h"

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> que;
        que.push(root);
        int result = 0;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                result = node->val;
                if (node->right) que.push(node->right);
                if (node->left) que.push(node->left);
            }
        }
        return result;
    }

    int findBottomLeftValueBest(TreeNode* root) {
        queue<TreeNode*> que;
        que.push(root);
        TreeNode* node = nullptr;

        while (!que.empty()) {
            node = que.front();
            que.pop();

            // 先右后左入队
            if (node->right) que.push(node->right);
            if (node->left) que.push(node->left);
        }

        // 循环结束后，node 保存的就是队列中最后一个弹出的节点
        return node->val;
    }
};