#ifndef LEETCODE_EXERCISE_LINKED_LIST_H
#define LEETCODE_EXERCISE_LINKED_LIST_H

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#endif //LEETCODE_EXERCISE_LINKED_LIST_H
