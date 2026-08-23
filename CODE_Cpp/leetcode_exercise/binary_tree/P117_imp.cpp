#include "binary_tree.h"

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;

        Node* leftmost = root; // 记录当前层的起始节点

        while (leftmost) {
            Node dummy(0);     // 虚拟头节点，用于串联下一层的节点
            Node* tail = &dummy; // 下一层链表的尾指针
            Node* head = leftmost;

            // 遍历当前层的链表
            while (head) {
                if (head->left) {
                    tail->next = head->left;
                    tail = tail->next;
                }
                if (head->right) {
                    tail->next = head->right;
                    tail = tail->next;
                }
                head = head->next; // 移动到当前层的下一个节点
            }

            // 进入下一层
            leftmost = dummy.next;
        }

        return root;
    }
};