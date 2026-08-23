#include <unordered_map>

#include "binary_tree.h"

class Solution {
    unordered_map<int, int> inorderMap;
public:
    TreeNode* build(vector<int>& inorder, vector<int>& preorder, int inStart, int inEnd, int preStart, int preEnd) {
        if (inStart > inEnd || preStart > preEnd) return nullptr;
        TreeNode* root = new TreeNode(preorder.at(preStart));
        int middle = inorderMap[root->val];
        root->left = build(inorder, preorder, inStart, middle - 1, preStart+1, preStart + middle - inStart);
        root->right = build(inorder, preorder, middle + 1, inEnd, preStart + middle - inStart + 1, preEnd);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder.at(i)] = i;
        }
        return build(inorder, preorder, 0, inorder.size()-1, 0, preorder.size()-1);
    }
};
