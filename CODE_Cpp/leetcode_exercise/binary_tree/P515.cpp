#include "binary_tree.h"

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int maxVal = INT_MIN;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();q.pop();
                if (node->val > maxVal) maxVal = node->val;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(maxVal);
        }
        return res;
    }
};