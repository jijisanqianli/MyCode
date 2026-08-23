#include "linked_list.h"

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head1 = l1;
        ListNode* head2 = l2;
        ListNode* prev = nullptr;
        int carry = 0;
        while (head1 != nullptr && head2 != nullptr) {
            int sum = head1->val + head2->val + carry;
            head1->val = sum % 10;
            carry = sum / 10;
            prev = head1;
            head1 = head1->next;
            head2 = head2->next;
        }
        if (head1 == nullptr && head2 != nullptr) {
            prev->next=head2;
            head1 = head2;
        }
        while (carry != 0 && head1 != nullptr) {
            int sum = head1->val + carry;
            head1->val = sum % 10;
            carry = sum / 10;
            prev = head1;
            head1 = head1->next;
        }
        if (carry != 0) prev->next = new ListNode(carry);
        return l1;
    }
};
