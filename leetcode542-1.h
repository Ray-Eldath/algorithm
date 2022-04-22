//
// Created by ray-eldath on 22-4-22.
//
#ifndef ALGORITHM_LEETCODE542_1_H
#define ALGORITHM_LEETCODE542_1_H

#include "utils.h"
#include <queue>

using namespace std;

extern const int dx[];
extern const int dy[];

vector<vector<int>> updateMatrix1(vector<vector<int>> &mat) {
    queue<pair<int, int>> q;
    vector<vector<int>> r(mat.size(), vector<int>(mat[0].size()));
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            if (mat[i][j] == 0) {
                q.emplace(i, j);
            } else {
                r[i][j] = INT32_MAX;
            }
        }
    }
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            pair<int, int> f = q.front();
            q.pop();
            for (int j = 0; j < 4; j++) {
                int newX = f.first + dx[j];
                int newY = f.second + dy[j];
                if (newX >= 0 && newX < r.size() && newY >= 0 && newY < r[0].size() &&
                    r[newX][newY] == INT32_MAX) {
                    r[newX][newY] = r[f.first][f.second] + 1;
                    q.emplace(newX, newY);
                }
            }
        }
    }
    return r;
}

#endif //ALGORITHM_LEETCODE542_1_H
