#include "binary_tree.h"

class Solution {
public:
    void visit(TreeNode* node, string path, vector<string>& res) {
        if (node->left == nullptr && node->right == nullptr) {
            res.push_back(path);
        }
        if (node->left) {
            visit(node->left, path + "->" + to_string(node->left->val) , res);
        }
        if (node->right) {
            visit(node->right, path + "->" + to_string(node->right->val) , res);
        }
    }

    vector<string> binaryTreePaths1(TreeNode* root) {
        if (!root) return {};
        vector<string> res;
        string path=to_string(root->val);
        visit(root, path, res);
        return res;
    }

    void dfs(TreeNode* node, vector<int> path, vector<string>& res) {
        path.push_back(node->val);
        if (node->left == nullptr && node->right == nullptr) {
            string s = "";
            for (int i = 0; i < path.size(); ++i) {
                s += to_string(path[i]);
                if (i < path.size() - 1) {
                    s += "->";
                }
            }
            res.push_back(s);
        }else {
            if (node->left) dfs(node->left, path, res);
            if (node->right) dfs(node->right, path, res);
        }
        path.pop_back();
    }

    vector<string> binaryTreePaths2(TreeNode* root) {
        if (!root) return {};
        vector<string> res;
        vector<int> path;
        dfs(root, path, res);
        return res;
    }
};
