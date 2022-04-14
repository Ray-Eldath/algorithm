//
// Created by ray-eldath on 2022/4/11.
//
#include "utils.h"

using namespace std;

void moveZeroes(vector<int> &nums) {
    int i = 0, j = 0;
    while (j < nums.size()) {
        if (nums[j] != 0)
            nums[i++] = nums[j];
        j++;
    }
    for (; i < nums.size(); i++) nums[i] = 0;
}

int main() {
    printInplaceVector(empty<int>(), moveZeroes);
    printInplaceVector({0}, moveZeroes);
    printInplaceVector({0, 0}, moveZeroes);
    printInplaceVector({0, 1}, moveZeroes);
    printInplaceVector({1, 0, 0}, moveZeroes);
    printInplaceVector({0, 1, 0, 2, 3}, moveZeroes);
    printInplaceVector({1, 2, 3, 4, 5}, moveZeroes);
    printInplaceVector({9, 0, 1, 0, 2, 3}, moveZeroes);
}