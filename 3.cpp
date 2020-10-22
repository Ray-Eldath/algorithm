//
// Created by Ray Eldath on 2020/10/11.
//
#include "3.h"

using namespace std;

int main() {
    auto il = {6, 1, 2, 4, 6, 5};

    auto il1 = {1, 4, 6};
    auto il2 = {2, 2, 6, 6, 9};
    auto il1l = make_unique<List<int>>(il1);
    cout << "il1l: ";
    il1l->show();
    auto il2l = make_unique<List<int>>(il2);
    cout << "il2l: ";
    il2l->show();

    il1l->merge(il1l->begin(), il1l->size(), *il2l, il2l->begin(), il2l->size());
    cout << "il1l merged: ";
    il1l->show();

    auto l = make_unique<List<int>>(il);

    l->show();
    l->sort();
    l->show();
}