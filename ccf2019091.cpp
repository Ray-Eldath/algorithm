//
// Created by Ray Eldath on 2020/9/25.
//
#include <iostream>

using namespace std;

int main() {
    int n, m, t = 0, k = 0, p = 0;

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        t += temp;

        int q = 0;
        for (int j = 1; j <= m; j++) {
            cin >> temp;
            q += temp;
        }
        t += q;

        if (q < p) {
            p = q;
            k = i;
        }
    }

    cout << t << " " << k << " " << -p << endl;
}