#include "binary_tree.h"

class Solution {
    TreeNode* visit(TreeNode* root, TreeNode* big, TreeNode* small) {
        if (root==nullptr || root==big || root==small) return root;
        if (root->val > big->val) return visit(root->left, big, small);
        if (root->val < small->val) return visit(root->right, big, small);
        return root;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* big = p->val > q->val ? p : q;
        TreeNode* small = p->val > q->val ? q : p;
        return visit(root, big, small);
    }

    TreeNode* lowestCommonAncestorBest(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root != nullptr) {
            if (root->val > p->val && root->val > q->val) {
                root = root->left;  // 当前节点太大，LCA 在左子树
            } else if (root->val < p->val && root->val < q->val) {
                root = root->right; // 当前节点太小，LCA 在右子树
            } else {
                return root;        // 遇到分叉点或等于其中一个节点，即为 LCA
            }
        }
        return nullptr;
    }
};
