//
// Created by ray-eldath on 22-4-21.
//
#include "leetcode102.h"

void recur(TreeNode *root1, TreeNode *root2) {
    if (!(root1 && root2)) return;
    root1->val += root2->val;
    if (root2->left) {
        if (root1->left) {
            recur(root1->left, root2->left);
        } else {
            root1->left = root2->left;
        }
    }
    if (root2->right) {
        if (root1->right) {
            recur(root1->right, root2->right);
        } else {
            root1->right = root2->right;
        }
    }
}

TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
    if (root1) {
        recur(root1, root2);
        return root1;
    }
    return root2;
}

TreeNode *mergeTrees2(TreeNode *root1, TreeNode *root2) {
    if (!root1) return root2;
    if (!root2) return root1;
    auto merged = new TreeNode(root1->val + root2->val);
    merged->left = mergeTrees2(root1->left, root2->left);
    merged->right = mergeTrees2(root1->right, root2->right);
    return merged;
}

void test(TreeNode *root1, TreeNode *root2) {
    cout << levelOrderStr(mergeTrees(root1, root2));
}

int main() {
    test(new TreeNode(1,
                      new TreeNode(3,
                                   new TreeNode(5), nullptr), new TreeNode(2)),
         new TreeNode(2,
                      new TreeNode(1, nullptr, new TreeNode(4)),
                      new TreeNode(3, nullptr, new TreeNode(7))));
    test(new TreeNode(1), new TreeNode(1, new TreeNode(2), nullptr));
    test(nullptr, new TreeNode(1));
    test(new TreeNode(1), nullptr);
}