//
// Created by ray-eldath on 2022/4/16.
//
#include "utils.h"

using namespace std;

void recur(vector<vector<int>> &image, int sr, int sc, int newColor, int baseColor, bool visited[]) {
    if (sr < 0 || sr >= image.size() || sc < 0 || sc >= image[sr].size() || image[sr][sc] != baseColor) return;
    auto i = sr * image[sr].size() + sc;
    if (visited[i]) return;
    visited[i] = true;
    image[sr][sc] = newColor;
    recur(image, sr - 1, sc, newColor, baseColor, visited);
    recur(image, sr + 1, sc, newColor, baseColor, visited);
    recur(image, sr, sc - 1, newColor, baseColor, visited);
    recur(image, sr, sc + 1, newColor, baseColor, visited);
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
    bool *visited = new bool[image.size() * image[0].size()]{false};
    recur(image, sr, sc, newColor, image[sr][sc], visited);
    delete[] visited;
    return image;
}

void test(initializer_list<initializer_list<int>> xs, int sr, int sc, int newColor) {
    vector<vector<int>> v;
    for (const auto &item: xs) v.emplace_back(item);
    floodFill(v, sr, sc, newColor);
    for (const auto &x: v)
        printVector(x);
    cout << endl;
}

int main() {
    test({{1, 1, 1},
          {1, 1, 0},
          {1, 0, 1}}, 1, 1, 2);
    test({{1, 1, 1},
          {1, 1, 1},
          {1, 0, 1}}, 0, 2, 2);
    test({{0, 0, 0},
          {0, 0, 0}}, 0, 0, 2);
    test({{0, 0, 0},
          {0, 1, 1}}, 1, 1, 1);
    test({{0, 0, 0},
          {0, 1, 1}}, 1, 1, 2);
    test({{0, 0, 0},
          {0, 1, 1}}, 0, 0, 1);
    test({{0, 1, 1},
          {1, 1, 1}}, 0, 0, 2);
}