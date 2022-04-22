//
// Created by ray-eldath on 22-4-22.
//

#ifndef ALGORITHM_LISTNODE_H
#define ALGORITHM_LISTNODE_H

#include <initializer_list>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printList(ListNode *l) {
    while (l != nullptr) {
        std::cout << l->val << " ";
        l = l->next;
    }
    std::cout << std::endl;
}

ListNode *listOf(std::initializer_list<int> is) {
    auto n = new ListNode();
    auto x = n;
    for (int e: is) {
        n->next = new ListNode(e);
        n = n->next;
    }
    return x->next;
}

#endif //ALGORITHM_LISTNODE_H
