//
// Created by ray-eldath on 2022/4/11.
//
#include "utils.h"

using namespace std;

vector<int> twoSum(const vector<int> &numbers, int target) {
    int i = 0, j = numbers.size() - 1;
    while (i >= 0 && j < numbers.size()) {
        int sum = numbers[i] + numbers[j];
        if (sum == target)
            return {i + 1, j + 1};
        else if (sum > target) j--;
        else i++;
    }
    return {};
}

int main() {
    printVector(twoSum({1, 1}, 2));
    printVector(twoSum({-1, 0}, -1));
    printVector(twoSum({2, 7, 11, 15}, 9));
    printVector(twoSum({2, 3, 8, 9, 11, 20}, 19));
}
