//
// Created by ray-eldath on 22-4-22.
//
#include "leetcode542-1.h"
#include "leetcode542-2.h"

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

void test(initializer_list<initializer_list<int>> xs) {
    for (const auto &row: mapMatrixOf<int, vector<vector<int>>>(xs, updateMatrix2))
        printVector(row);
    cout << endl;
}

int main() {
    test({{0, 0, 0},
          {0, 1, 0},
          {0, 0, 0}});
    test({{0, 0, 0},
          {0, 1, 0},
          {1, 1, 1}});
    test({{0, 0, 0},
          {0, 1, 0},
          {1, 1, 1},
          {1, 1, 1},
          {1, 1, 0}});
    test({{0, 0, 0},
          {0, 1, 0},
          {1, 1, 1},
          {1, 1, 1}});
    test({{0}});
    test({{0, 0},
          {0, 0}});
}