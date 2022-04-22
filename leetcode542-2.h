//
// Created by ray-eldath on 22-4-22.
//

#ifndef ALGORITHM_LEETCODE542_2_H
#define ALGORITHM_LEETCODE542_2_H

#include "utils.h"
#include <queue>

using namespace std;

bool inMatrix(vector<vector<int>> &mat, int i, int j) {
    return i >= 0 && i < mat.size() && j >= 0 && j < mat[0].size();
}

vector<vector<int>> updateMatrix2(vector<vector<int>> &mat) {
    queue<pair<int, int>> q;
    vector<vector<int>> r(mat.size(), vector<int>(mat[0].size(), 0));
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            if (mat[i][j] == 1) {
                r[i][j] = INT32_MAX;
                for (int k = 0; k < 4; k++) {
                    int newI = i + dx[k];
                    int newJ = j + dy[k];
                    if (inMatrix(mat, newI, newJ) && mat[newI][newJ] == 0) {
                        q.emplace(i, j);
                        r[i][j] = 1;
                    }
                }
            }
        }
    }
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            pair<int, int> f = q.front();
            q.pop();
            int min = INT32_MAX;
            for (int k = 0; k < 4; k++) {
                int newI = f.first + dx[k];
                int newJ = f.second + dy[k];
                if (inMatrix(r, newI, newJ)) {
                    int v = r[newI][newJ];
                    if (r[newI][newJ] == INT32_MAX)
                        q.emplace(newI, newJ);
                    if (v < min) min = v;
                }
            }
            r[f.first][f.second] = min + 1;
        }
    }
    return r;
}

#endif //ALGORITHM_LEETCODE542_2_H