//
// Created by ray-eldath on 22-4-23.
//
#include "utils.h"

using namespace std;

void recur(int m, int n, int k, vector<int> &prefix, vector<vector<int>> &result) {
    if (prefix.size() == k) {
        result.emplace_back(prefix);
        return;
    }

    for (int i = m; i <= n - (k - prefix.size()) + 1; i++) {
        prefix.emplace_back(i);
        cout << "p: ";
        for (const auto &e: prefix) cout << e;
        cout << " [" << m << ", " << n << "] " << k << endl;
        recur(i + 1, n, k, prefix, result);
        prefix.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<int> p;
    vector<vector<int>> r;
    recur(1, n, k, p, r);
    return r;
}

int main() {
    printDigits<int>(combine(4, 2));
    printDigits<int>(combine(1, 1));
    printDigits<int>(combine(4, 3));
    printDigits<int>(combine(4, 4));
}