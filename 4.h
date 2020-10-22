//
// Created by Ray Eldath on 2020/10/16.
//
#include "2.h"

template<typename T>
class Stack : public Vector<T> {
public:
    Stack() = default;

    void push(const T &e) { this->insert(this->size(), e); }

    T pop() {
        auto pos = this->size() - 1;
        T r = this->at(pos);
        this->remove(pos);
        return r;
    }

    T &top() { return this->at(this->size() - 1); }
};