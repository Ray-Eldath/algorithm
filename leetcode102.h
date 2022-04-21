//
// Created by ray-eldath on 22-4-21.
//

#ifndef ALGORITHM_LEETCODE102_H
#define ALGORITHM_LEETCODE102_H

#endif //ALGORITHM_LEETCODE102_H

#include <queue>
#include <vector>
#include <iostream>
#include <sstream>
#include "bintree.h"

using namespace std;

vector<vector<int>> levelOrder(TreeNode *root) {
    if (!root) return {};
    vector<vector<int>> r;
    queue<TreeNode *> q;
    q.push({root});
    r.push_back({root->val});
    while (!q.empty()) {
        int c = q.size();
        vector<int> nextResult;
        for (int i = 0; i < c; i++) {
            auto n = q.front();
            q.pop();
            if (n->left) {
                q.emplace(n->left);
                nextResult.emplace_back(n->left->val);
            }
            if (n->right) {
                q.emplace(n->right);
                nextResult.emplace_back(n->right->val);
            }
        }
        if (!nextResult.empty()) r.emplace_back(nextResult);
    }
    return r;
}

string levelOrderStr(TreeNode *root) {
    stringstream ss;
    ss << "[";
    const auto &r = levelOrder(root);
    for (int i = 0; i < r.size(); i++) {
        ss << "[";
        const auto &l = r[i];
        for (int j = 0; j < l.size(); j++) {
            ss << l[j];
            if (j < l.size() - 1) ss << ",";
        }
        ss << "]";
        if (i < r.size() - 1) ss << ",";
    }
    ss << "]" << endl;
    return ss.str();
}