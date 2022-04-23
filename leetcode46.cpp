//
// Created by ray-eldath on 22-4-23.
//
#include "utils.h"

using namespace std;

void backtrack2(int n, vector<int> &nums, vector<vector<int>> &result) {
    if (n == nums.size() - 1) {
        result.emplace_back(nums);
        return;
    }

    for (int i = n; i < nums.size(); i++) {
        iter_swap(nums.begin() + n, nums.begin() + i);
        backtrack2(n + 1, nums, result);
        iter_swap(nums.begin() + n, nums.begin() + i);
    }
}

vector<vector<int>> permute2(vector<int> &nums) {
    vector<vector<int>> r;
    backtrack2(0, nums, r);
    return r;
}

void backtrack(vector<int> &prefix, vector<int> &nums, vector<vector<int>> &result) {
    if (nums.size() == 2) {
        prefix.emplace_back(nums[0]);
        prefix.emplace_back(nums[1]);
        result.push_back(prefix);
        iter_swap(prefix.end() - 1, prefix.end() - 2);
        result.push_back(prefix);
        prefix.pop_back();
        prefix.pop_back();
        return;
    }

    for (int i = 0; i < nums.size(); i++) {
        int nn = nums[i];
        prefix.emplace_back(nn);
//        cout << "prefix: ";
//        printVector<int>(prefix);
        nums.erase(nums.cbegin() + i);
        backtrack(prefix, nums, result);
        nums.insert(nums.cbegin() + i, nn);
        prefix.pop_back();
    }
}

vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> r;
    if (nums.size() == 1) {
        r.emplace_back(nums);
    } else {
        vector<int> p;
        backtrack(p, nums, r);
    }
    return r;
}

void test(const vector<int> &nums) {
//    printDigits<int>(permute(n));
    auto n = removeConst(nums);
    printDigits<int>(permute2(n));
}

int main() {
    test({1, 2, 3});
    test({1, 2, 3, 4});
    test({0, 1});
    test({1});
}