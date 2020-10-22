//
// Created by Ray Eldath on 2020/9/30.
//
#include <iostream>
#include <vector>

using namespace std;

void halistoneRecursive(int n, vector<int> &e) {
    if (n == 1) {
        e.push_back(1);
        return;
    } else if (n % 2 == 0) {
        e.push_back(n);
        halistoneRecursive(n / 2, e);
    } else {
        e.push_back(n);
        halistoneRecursive(3 * n + 1, e);
    }
}

void halistoneIterate(int n, vector<int> &e) {
    auto nn = n;
    while (nn != 1) {
        e.push_back(nn);
        nn = nn % 2 == 0 ? nn / 2 : 3 * nn + 1;
    }
    e.push_back(1);
}

int main() {
    vector<int> d;
    const int n = 7;

    halistoneRecursive(n, d);
    for (auto a:d)
        cout << a << " ";
    cout << endl;

    d.clear();

    halistoneIterate(n, d);
    for (auto a:d)
        cout << a << " ";
    cout << endl;
}
