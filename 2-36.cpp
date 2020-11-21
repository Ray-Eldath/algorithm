//
// Created by Ray Eldath on 2020/10/6.
//
#include "2-34.h"
#include "utils.h"
#include <iostream>
#include <vector>

using namespace std;

vector<int> eratosthenes(int n) {
    auto bits = make_unique<Bitmap>(n);
    vector<int> r;

    bits->clear(2);
    for (long i = 2; i < n; i++) {
        if (!bits->test(i)) {
            r.push_back(i);
            for (long j = i * i; j < n; j += i)
                bits->set(j);
        }
    }

    return r;
}

int main() {
    for (auto i:eratosthenes(100000))
        cout << i << " ";
}