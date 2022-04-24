//
// Created by ray-eldath on 22-4-24.
//
#include <algorithm>
#include "utils.h"

// #define DEBUG

using namespace std;

using Results = vector<vector<int>>;

void backtrack(int k, int sum, Results &results, vector<int> &prefix, vector<int> &candidates, int target) {
    if (sum == target) {
        results.emplace_back(prefix);
    }
#ifdef DEBUG
    printVector(prefix);
#endif

    for (int i = k; i < candidates.size(); i++) {
        auto n = candidates[i];
        if (sum + n > target) return;
        sum += n;
        prefix.emplace_back(n);
        backtrack(i, sum, results, prefix, candidates, target);
        prefix.pop_back();
        sum -= n;
    }
}

Results combinationSum(vector<int> &candidates, int target) {
    Results r;
    vector<int> p;
    sort(candidates.begin(), candidates.end());
    backtrack(0, 0, r, p, candidates, target);
    return r;
}

void test(const vector<int> &candidates, int target) {
    auto c = removeConst(candidates);
    printDigits(combinationSum(c, target));
    cout << endl;
}

int main() {
    test({2, 3, 6, 7}, 7);
    test({2, 3, 5}, 8);
    test({2}, 1);
    test({1}, 30);
    test({1, 2}, 7);
    test({2, 7, 6, 3, 5, 1}, 9);
}