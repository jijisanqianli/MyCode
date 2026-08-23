#include "binary_tree.h"

class Solution {
    void visit(TreeNode* root, vector<int>& res,int& count,int& max_count,TreeNode*& pre) {
        if (root == nullptr) return;
        visit(root->left, res, count, max_count, pre);
        if (pre == nullptr || pre->val != root->val) count = 1;
        else count++;
        if (count > max_count) {
            max_count = count;
            res.clear();
        }
        if (count == max_count) res.push_back(root->val);
        pre = root;
        visit(root->right, res, count, max_count, pre);
    }

public:
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        int count = 0, max_count = 0;
        TreeNode* pre = nullptr;
        visit(root, res, count, max_count, pre);
        return res;
    }
};
