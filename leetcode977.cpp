//
// Created by ray-eldath on 2022/4/11.
//
#include "utils.h"

using namespace std;

vector<int> sortedSquares(const vector<int> &nums) {
    vector<int> r;
    int neg = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] >= 0) break;
        neg = i;
    }

    int i = neg, j = neg + 1;
    while (i >= 0 && j < nums.size()) {
        int is = nums[i] * nums[i];
        int js = nums[j] * nums[j];
        if (is >= js) {
            r.push_back(js);
            j++;
        } else {
            r.push_back(is);
            i--;
        }
    }
    for (; i >= 0; i--) r.push_back(nums[i] * nums[i]);
    for (; j < nums.size(); j++) r.push_back(nums[j] * nums[j]);
    return r;
}

int main() {
    printVector(sortedSquares({-4, -1, 0, 3, 10}));
    printVector(sortedSquares({-7, -3, 2, 3, 11}));
}
