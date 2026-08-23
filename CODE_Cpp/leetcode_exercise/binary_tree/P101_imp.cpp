#include "binary_tree.h"

class Solution {
public:
    vector<TreeNode*> leftOrder(TreeNode* root) {
        stack<TreeNode*> st;
        vector<TreeNode*> res;
        st.push(root);
        while (!st.empty()) {
            TreeNode* cur = st.top();
            st.pop();
            res.push_back(cur);
            if (cur) {
                st.push(cur->left);
                st.push(cur->right);
            }
        }
        return res;
    }

    bool isSymmetric0(TreeNode* root) {
        if (root == nullptr) return true;
        if (root->left == nullptr && root->right == nullptr) return true;
        if (root->left == nullptr && root->right != nullptr) return false;
        if (root->right == nullptr && root->left != nullptr) return false;
        if (root->left->val != root->right->val) return false;
        vector<TreeNode*> left = leftOrder(root->left);
        int i = 0;
        stack<TreeNode*> st;
        st.push(root->right);
        while (!st.empty()) {
            TreeNode* cur = st.top();
            st.pop();
            if (i >= left.size()) return false;
            if (cur && left[i]!=nullptr) {
                if (cur->val != left[i]->val) return false;
            }else if (cur == nullptr && left[i] != nullptr || cur != nullptr && left[i] == nullptr) {
                return false;
            }
            i++;
            if (cur) {
                st.push(cur->right);
                st.push(cur->left);
            }
        }
        return true;
    }

    bool isSymmetric1(TreeNode* root) {
        if (root == nullptr) return true;
        queue<TreeNode*> que;
        que.push(root->left);
        que.push(root->right);
        while (!que.empty()) {
            TreeNode* leftNode = que.front(); que.pop();
            TreeNode* rightNode = que.front(); que.pop();
            if (!leftNode && !rightNode) continue;
            if (!leftNode || !rightNode || (leftNode->val != rightNode->val)) return false;
            que.push(leftNode->left);
            que.push(rightNode->right);

            que.push(leftNode->right);
            que.push(rightNode->left);
        }
        return true;
    }

    bool compare(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right == nullptr) return true;
        if (left == nullptr && right != nullptr) return false;
        if (left != nullptr && right == nullptr) return false;
        if (left->val != right->val) return false;
        return compare(left->left, right->right) && compare(left->right, right->left);
    }

    bool isSymmetric2(TreeNode* root) {
        if (root == nullptr) return true;
        return compare(root->left, root->right);
    }
};