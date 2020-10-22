//
// Created by Ray Eldath on 2020/10/7.
//

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
size_t binSearch(const T *elem, T e, size_t lo, size_t hi) {
    while (lo < hi) {
        auto mi = (lo + hi) >> 1u;
        e < elem[mi] ? hi = mi : lo = mi + 1;
    }
    return lo - 1;
}

int main() {
    int v[][4] = {
            {1, 3,  5,  8},
            {4, 5,  7,  9},
            {5, 6,  9,  10},
            {9, 13, 17, 19}
    };

    constexpr auto target = 5;

    auto i = 0;
    auto j = binSearch(v[0], target, 0, 4);

    while (i < 3 && j < 3) {
        if (v[i][j] < target) i--;
        else if (v[i][j] > target) j--;
        else {
            cout << "found " << target << " at [" << i << "][" << j << "]" << endl;
            i--;
            j--;
        }
    }
}