//
// Created by ray-eldath on 2022/4/9.
//
#include <vector>
#include <iostream>

using namespace std;

int recur(const vector<int> &nums, int target, int L, int R) {
    if (L == R) return nums[L] == target ? L : -1;
    int C = L + (R - L) / 2;
    return target <= nums[C] ? recur(nums, target, L, C) : recur(nums, target, C + 1, R);
}

int search(const vector<int> &nums, int target) {
    return recur(nums, target, 0, nums.size() - 1);
}

int main() {
    cout << search({1, 2, 3, 9}, 4) << endl;
    cout << search({1, 2, 3, 9}, 9) << endl;
    cout << search({1, 2, 3, 9}, 1) << endl;
    cout << search({1}, 1) << endl;
    cout << search({1}, -1) << endl;
    return 0;
}