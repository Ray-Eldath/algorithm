//
// Created by ray-eldath on 22-4-24.
//
#include "utils.h"
#include <algorithm>

using namespace std;

using Results = vector<vector<int>>;

void backtrack(int k, int sum, vector<int> &prefix, Results &results, vector<int> &candidates, int target) {
    if (sum == target)
        results.emplace_back(prefix);

    int nn = 0;
    for (int i = k; i < candidates.size(); i++) {
        auto n = candidates[i];
//        cout << "nn=" << nn << " n=" << n << endl;
        if (sum + n > target) return;
        if (nn == n) continue;
        nn = n;
        sum += n;
        prefix.emplace_back(n);
        backtrack(i + 1, sum, prefix, results, candidates, target);
        prefix.pop_back();
        sum -= n;
    }
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    vector<int> p;
    Results r;
    sort(candidates.begin(), candidates.end());
    backtrack(0, 0, p, r, candidates, target);
    return r;
}

void test(const vector<int> &candidates, int target) {
    auto c = removeConst(candidates);
    printDigits(combinationSum2(c, target));
    cout << endl;
}

int main() {
    test({1, 2, 3, 4}, 5);
    test({1, 2, 2, 3}, 5);
    test({10, 1, 2, 7, 6, 1, 5}, 8);
    test({2, 5, 2, 1, 2}, 5);
    test({1}, 1);
    printDigits(measure([]() -> Results {
        auto c = removeConst<vector<int>>({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
        return combinationSum2(c, 20);
    }));
}