//
// Created by Ray Eldath on 2020/10/5.
//
#include "2.h"

int main() {
    auto l = {3, 3, 2, 5, 9, 6, 8};
    auto v = make_unique<Vector<int>>(l);
    v->sort();

    v->show();
    std::cout << "v done." << std::endl;

    for (auto i : {1, 2, 4, 6})
        std::cout << v->search(i) - v->begin() << " ";
    std::cout << std::endl;
    std::cout << "search done." << std::endl;

    v->remove(0);
    v->uniquify();

    v->show();
    std::cout << "unification done." << std::endl;
}