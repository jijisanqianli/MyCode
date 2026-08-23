#include <unordered_map>

#include "binary_tree.h"

class Solution {
    unordered_map<int, int> inorderMap;

    TreeNode* build(vector<int>& inorder, vector<int>& postorder, int inStart, int inEnd, int postStart, int postEnd) {
        if (inStart > inEnd || postStart > postEnd) return nullptr;
        TreeNode* root = new TreeNode(postorder.at(postEnd));
        int middle = inorderMap[root->val];
        root->left = build(inorder, postorder, inStart, middle - 1, postStart, postStart + middle - inStart-1);
        root->right = build(inorder, postorder, middle + 1, inEnd, postStart + middle - inStart, postEnd - 1);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder.at(i)] = i;
        }
        return build(inorder, postorder, 0, inorder.size()-1,0, postorder.size()-1);
    }
};