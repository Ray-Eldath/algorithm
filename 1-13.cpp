//
// Created by Ray Eldath on 2020/10/4.
//
#include <iostream>

using namespace std;

unsigned long powerRec(unsigned int n) {
    if (n == 0)
        return 1;
    else
        return powerRec(n - 1) << 1u;
}

unsigned long powerTailRec(int n, unsigned long v = 1) {
    if (n == 0)
        return v;
    else
        return powerTailRec(n - 1, v << 1u);
}

unsigned long power(int n) {
    unsigned long pow = 1;
    while (n--)
        pow <<= 1u;
    return pow;
}

inline unsigned long squ(unsigned long x) { return x * x; }

unsigned long powRec(unsigned int n) {
    if (n == 0)
        return 1;
    else if (n & 1u)
        return squ(powRec(n >> 1u)) << 1u;
    else
        return squ(powRec(n >> 1u));
}

unsigned long powTailRec(unsigned int n, unsigned long v = 1, unsigned long p = 2) {
    if (n == 0)
        return v;
    else if (n & 1u)
        return powTailRec(n >> 1u, v * p, squ(p));
    else
        return powTailRec(n >> 1u, v, squ(p));
}

unsigned long pow(unsigned int n) {
    unsigned long v = 1, p = 2;

    while (n > 0) {
        if (n & 1u)
            v *= p;

        n >>= 1u;
        p *= p;
    }

    return v;
}

int main() {
    constexpr long v = 5;
    cout << powerRec(v) << endl;
    cout << powerTailRec(v) << endl;
    cout << power(v) << endl;

    cout << powRec(v) << endl;
    cout << powTailRec(v) << endl;
    cout << pow(v) << endl;
}