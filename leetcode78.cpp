//
// Created by ray-eldath on 22-4-24.
//
#include "utils.h"

using namespace std;

void backtrack(int k, vector<int> &prefix, vector<int> &nums, vector<vector<int>> &result) {
    result.emplace_back(prefix);

    for (int i = k; i < nums.size(); i++) {
        prefix.emplace_back(nums[i]);
        backtrack(i + 1, prefix, nums, result);
        prefix.pop_back();
    }
}

vector<vector<int>> subsets(vector<int> &nums) {
    vector<int> p;
    vector<vector<int>> r;
    backtrack(0, p, nums, r);
    return r;
}

void test(const vector<int> &nums) {
    auto n = removeConst(nums);
    printDigits(subsets(n));
}

int main() {
    test({1, 2, 3});
    test({});
    test({1});
}