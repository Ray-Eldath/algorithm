//
// Created by ray-eldath on 22-4-21.
//
#include "leetcode102.h"

using namespace std;

void test(TreeNode *root) {
    cout << levelOrderStr(root);
}

int main() {
    test(new TreeNode(2,
                      new TreeNode(1,
                                   nullptr, new TreeNode(4)),
                      new TreeNode(3,
                                   nullptr, new TreeNode(7))));
    test(new TreeNode(1));
    test(nullptr);
}