//
// Created by Ray Eldath on 2020/9/29.
//
#include <iostream>
#include <vector>

using namespace std;

void subset(vector<vector<int>> &result, vector<int> &current, const vector<int> &nums, int start) {
    result.push_back(current);
    for (int i = start; i < nums.size(); i++) {
        current.push_back(nums[i]);
        subset(result, current, nums, start + 1);
        current.erase(current.cend() - 1);
    }
}

int main() {
    int n, m;
    vector<int> in;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> m;
        in.emplace_back(m);
    }

    vector<vector<int>> r;
    vector<int> c;
    subset(r, c, in, 0);
    for (auto &&i : r) {
        cout << "[";
        for (auto j:i)
            cout << j << " ";
        cout << "]" << endl;
    }
    return 0;
}