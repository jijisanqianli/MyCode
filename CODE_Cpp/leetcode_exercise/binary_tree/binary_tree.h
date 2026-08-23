#ifndef LEETCODE_EXERCISE_BINARY_TREE_H
#define LEETCODE_EXERCISE_BINARY_TREE_H
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#endif //LEETCODE_EXERCISE_BINARY_TREE_H
