//
// Created by ray-eldath on 2022/4/16.
//
#include "utils.h"
#include <queue>

using namespace std;

int bfs(vector<vector<int>> &grid, int r, int c) {
    queue<pair<int, int>> q;
    q.emplace(make_pair(r, c));
    int t = 0;
    while (!q.empty()) {
        const auto n = q.front();
        q.pop();
        const auto i = n.first, j = n.second;
        if (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size() && grid[i][j] == 1) {
            t++;
            grid[i][j] = 0;
            q.emplace(make_pair(n.first + 1, n.second));
            q.emplace(make_pair(n.first - 1, n.second));
            q.emplace(make_pair(n.first, n.second + 1));
            q.emplace(make_pair(n.first, n.second - 1));
        }
    }
    return t;
}

int dfs(vector<vector<int>> &grid, int r, int c) {
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] == 0) return 0;
    grid[r][c] = 0;
    return dfs(grid, r + 1, c) +
           dfs(grid, r - 1, c) +
           dfs(grid, r, c + 1) +
           dfs(grid, r, c - 1) + 1;
}

int maxAreaOfIsland(vector<vector<int>> &grid) {
    int max = 0;
    for (int i = 0; i < grid.size(); i++) {
        const auto &row = grid[i];
        for (int j = 0; j < row.size(); j++) {
            if (grid[i][j] == 1) {
                int d = dfs(grid, i, j);
                max = d > max ? d : max;
            }
        }
    }
    return max;
}

void test(const initializer_list<initializer_list<int>> &grid) {
    vector<vector<int>> v;
    for (const auto &item: grid) v.emplace_back(item);
    cout << maxAreaOfIsland(v) << endl;
}

int main() {
    test({{1, 0, 0},
          {0, 1, 0},
          {0, 1, 1}});
    test({{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
          {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
          {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}});
    test({{0, 0, 0, 0, 0, 0, 0, 0}});
}