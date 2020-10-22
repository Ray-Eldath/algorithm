//
// Created by Ray Eldath on 2020/9/30.
//
#include <iostream>
#include <vector>

using namespace std;

void hanoi(int n, vector<int> &x, vector<int> &y, vector<int> &z) {
    if (n > 0) {
        hanoi(n - 1, x, z, y);

        z.push_back(x.back());
        x.pop_back();

        hanoi(n - 1, y, x, z);
    }
}

int main() {
    auto x = vector<int>{1, 2, 3};
    auto y = vector<int>{};
    auto z = vector<int>{};
    hanoi(3, x, y, z);
}