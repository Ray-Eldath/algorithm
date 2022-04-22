//
// Created by ray-eldath on 22-4-22.
//
#include <queue>
#include "utils.h"

using namespace std;

inline void rot(int i, int j, vector<vector<int>> &grid, queue<pair<int, int>> &q, int &fresh) {
    if (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size()) {
        if (grid[i][j] == 1) {
            grid[i][j] = 2;
            q.emplace(make_pair(i, j));
            fresh--;
        }
    }
}

int orangesRotting(vector<vector<int>> &grid) {
    int fresh = 0, count = -1;
    queue<pair<int, int>> q;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 1) fresh++;
            else if (grid[i][j] == 2) q.emplace(make_pair(i, j));
        }
    }
    if (fresh == 0) return 0;
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            auto f = q.front();
            q.pop();
            rot(f.first - 1, f.second, grid, q, fresh);
            rot(f.first + 1, f.second, grid, q, fresh);
            rot(f.first, f.second - 1, grid, q, fresh);
            rot(f.first, f.second + 1, grid, q, fresh);
        }
        count++;
    }
    return fresh == 0 ? count : -1;
}

void test(initializer_list<initializer_list<int>> xs) {
    cout << mapMatrixOf<int, int>(xs, orangesRotting) << endl;
}

int main() {
    test({{2, 1, 1},
          {1, 1, 0},
          {0, 1, 1}});
    test({{2, 1, 1},
          {1, 1, 0},
          {1, 0, 1}});
    test({{0, 2}});
    test({{0}});
    test({{1}});
    test({{2}});
}