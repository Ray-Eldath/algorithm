//
// Created by ray-eldath on 22-4-22.
//
#include "listnode.h"

using namespace std;

ListNode *recur(ListNode *c, ListNode *prev) {
    if (!c) return prev;
    ListNode *r = recur(c->next, c);
    c->next = prev;
    return r;
}

ListNode *reverseList(ListNode *head) {
    return recur(head, nullptr);
}

ListNode *reverseList2(ListNode *head) {
    if (!(head && head->next)) return head;
    ListNode *newHead = reverseList2(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

void test(initializer_list<int> xs) {
    printList(reverseList(listOf(xs)));
    printList(reverseList2(listOf(xs)));
}

int main() {
    test({1, 2, 3, 4, 5});
    test({1});
    test({});
}
