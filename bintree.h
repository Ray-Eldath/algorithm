//
// Created by ray-eldath on 22-4-21.
//

#ifndef ALGORITHM_BINTREE_H
#define ALGORITHM_BINTREE_H

#endif //ALGORITHM_BINTREE_H

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};