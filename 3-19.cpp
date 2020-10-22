//
// Created by Ray Eldath on 2020/10/15.
//
#include "3.h"

using namespace std;

void josephus(int n, int k) {
    auto l = make_unique<List<int>>();

    l->trailer()->succ = l->header();
    l->header()->pred = l->trailer();

    for (int i = 1; i <= n; i++)
        l->push_back(i);

    auto x = l->begin();
    auto xx = 1;
    while (n > 1) {
        x = x->succ;
        if (x->data != 0 && ++xx == k) {
            cout << l->remove(x) << endl;
            n--;
            xx = 0;
        }
    }
}

int main() {
    josephus(8, 3);
}