//
// Created by Ray Eldath on 2020/10/6.
//

#include "2-34.h"
#include <iostream>
#include <climits>
#include <memory>

using namespace std;

int main() {
    auto m = make_unique<Bitmap>(CHAR_MAX);
    const auto a = string("AAABBBcDEEFghIIJ");
    for (auto c: a)
        m->set(c);
    for (int i = 0; i < CHAR_MAX; i++)
        if (m->test(i))
            cout << (char) i << " ";
}