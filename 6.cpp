//
// Created by Ray Eldath on 2020/11/2.
//

#include "6.h"

int main() {
    auto gm = new GraphMatrix<int, int>();
    gm->insert(1);
    gm->remove(1);
    delete gm;
}