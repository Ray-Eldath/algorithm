//
// Created by ray-eldath on 2022/4/11.
//
#include "utils.h"

using namespace std;

void reverse(vector<int> &nums, int L, int R) {
    while (L < R) {
        int t = nums[L];
        nums[L] = nums[R];
        nums[R] = t;
        L += 1;
        R -= 1;
    }
}

void rotate(vector<int> &nums, int k) {
    if ((k = k % nums.size()) > 0) {
        reverse(nums, 0, nums.size() - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.size() - 1);
    }
}

inline int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void rotate2(vector<int> &nums, int k) {
    for (int start = 0; start < gcd(k, nums.size()); start++) {
        int p = nums[start];
        int current = start;
        int count = 0;
        do {
            int target = (current + k) % nums.size();
            int prev = nums[target];
            nums[target] = p;
            p = prev;
            current = target;
            count++;
        } while (current != start);
    }
}

int test(initializer_list<int> nums, int k) {
    vector<int> v{nums}, v2{nums};
    rotate(v, k);
    printVector(v);
    rotate2(v2, k);
    printVector(v2);
}

int main() {
    test({1}, 0);
    test({1}, 1);
    test({1}, 2);
    test({1}, 3);
    test({1, 2, 3, 4, 5, 6, 7}, 3);
    test({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3);
    test({1, 2, 3, 4, 5}, 7);
    test({1, 2, 3, 4, 5}, 1);
    test({1, 2, 3, 4}, 2);
    test({-1, -100, 3, 99}, 2);
    return 0;
}