#include <unordered_map>

#include "binary_tree.h"

class Solution {
    unordered_map<int, int> postorderMap;

    TreeNode* build(vector<int>& preorder, vector<int>& postorder, int preStart, int preEnd, int postStart, int postEnd) {
        if (preStart > preEnd || postStart > postEnd) return nullptr;

        // 当前子树的根节点是前序遍历的第一个元素
        TreeNode* root = new TreeNode(preorder.at(preStart));

        // 如果当前区间只有一个节点，直接返回该根节点（避免后续 preStart + 1 越界）
        if (preStart == preEnd) return root;

        // 前序遍历中根节点紧接着的下一个节点，就是左子树的根节点
        int leftRootVal = preorder.at(preStart + 1);

        // 在后序遍历中找到左子树根节点的位置
        int middle = postorderMap[leftRootVal];

        // 计算左子树的节点数量
        int leftSize = middle - postStart + 1;

        // 递归构建左子树和右子树
        root->left = build(preorder, postorder, preStart + 1, preStart + leftSize, postStart, middle);
        root->right = build(preorder, postorder, preStart + leftSize + 1, preEnd, middle + 1, postEnd - 1);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& postorder) {
        // 建立后序遍历值到索引的映射
        for (int i = 0; i < postorder.size(); i++) {
            postorderMap[postorder.at(i)] = i;
        }
        return build(preorder, postorder, 0, preorder.size() - 1, 0, postorder.size() - 1);
    }
};