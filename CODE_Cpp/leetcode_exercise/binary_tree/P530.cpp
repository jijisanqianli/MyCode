#include "binary_tree.h"

class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        int result = INT_MAX;
        while (cur != nullptr || !st.empty()) {
            if (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }else {
                cur = st.top();st.pop();
                if (pre != nullptr) {
                    result = min(result, cur->val - pre->val);
                }
                pre = cur;
                cur = cur->right;
            }
        }
        return result;
    }
};
