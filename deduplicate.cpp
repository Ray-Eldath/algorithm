//
// Created by Ray Eldath on 2020/10/9.
//

#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    vector<int> d{5, 5, 9, 8, 3, 3, 3, 7, 5};

    int max = INT32_MIN;
    for (auto i : d)
        if (i > max)
            max = i;
    max++;

    int F[max], T[max], top = 0, kk = 0;
    memset(F, 0, sizeof(int) * max);
    memset(T, 0, sizeof(int) * max);
    for (int k : d) {
        if (T[F[k]] != k) {
            F[k] = top++;
            T[F[k]] = k;
            kk++;
        }
    }

    for (int i = 0; i < kk; i++)
        cout << T[i] << endl;
}