//
// Created by Ray Eldath on 2020/9/25.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<pair<int, int>> v;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v.emplace_back(make_pair(a, b));
    }

    int m[5] = {0};
    for (auto p:v) {
        if (find(v.cbegin(), v.cend(), make_pair(p.first, p.second + 1)) != v.cend() &&
            find(v.cbegin(), v.cend(), make_pair(p.first, p.second - 1)) != v.cend() &&
            find(v.cbegin(), v.cend(), make_pair(p.first + 1, p.second)) != v.cend() &&
            find(v.cbegin(), v.cend(), make_pair(p.first - 1, p.second)) != v.cend()) {
            int j = 0;

            j += find(v.cbegin(), v.cend(), make_pair(p.first + 1, p.second + 1)) != v.cend();
            j += find(v.cbegin(), v.cend(), make_pair(p.first + 1, p.second - 1)) != v.cend();
            j += find(v.cbegin(), v.cend(), make_pair(p.first - 1, p.second - 1)) != v.cend();
            j += find(v.cbegin(), v.cend(), make_pair(p.first - 1, p.second + 1)) != v.cend();

            m[j]++;
        }
    }

    for (auto result:m) {
        cout << result << endl;
    }
}