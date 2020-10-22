//
// Created by Ray Eldath on 2020/10/16.
//
#include "4.h"

using namespace std;

int main() {
    auto s = make_unique<Stack<int>>();
    s->show();
    s->push(3);
    cout << s->pop() << endl;
    s->push(5);
    s->push(7);
    cout << s->top() << endl;
    s->show();
}
