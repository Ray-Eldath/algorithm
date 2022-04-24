//
// Created by ray-eldath on 22-4-24.
//
#include <algorithm>
#include "utils.h"

using namespace std;

using Results = vector<vector<int>>;

void backtrack(int k, vector<int> &prefix, Results &results, vector<int> &nums) {
    results.emplace_back(prefix);

    int nn = INT32_MIN;
    for (int i = k; i < nums.size(); i++) {
        auto n = nums[i];
        if (n == nn) continue;
        nn = n;
        prefix.emplace_back(n);
        backtrack(i + 1, prefix, results, nums);
        prefix.pop_back();
    }
}

Results subsetsWithDup(vector<int> &nums) {
    Results r;
    vector<int> p;
    sort(nums.begin(), nums.end());
    backtrack(0, p, r, nums);
    return r;
}

void test(const vector<int> &nums) {
    auto n = removeConst(nums);
    printDigits(subsetsWithDup(n));
    cout << endl;
}

int main() {
    test({1, 2, 2});
    test({4, 4, 4, 1, 4});
    test({1, 2, 3});
    test({0});
}
