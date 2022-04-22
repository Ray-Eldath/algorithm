//
// Created by ray-eldath on 22-4-22.
//
#include "listnode.h"

using namespace std;

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;
    if (list1->val < list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}

int main() {
    printList(listOf({1, 2, 4}));
    printList(listOf({1, 3, 4}));
    printList(mergeTwoLists(listOf({1, 2, 4}), listOf({1, 3, 4})));
}