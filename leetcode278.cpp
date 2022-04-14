#include <iostream>
#include <vector>

using namespace std;
int badVersion;

bool isBadVersion(int version) {
    return version >= badVersion;
}

int recur(int L, int R) {
    if (L == R) return L;
    int C = L + (R - L) / 2;
    return isBadVersion(C) ? recur(L, C) : recur(C + 1, R);
}

int firstBadVersion(int n) {
    return recur(1, n);
}

int main() {
    badVersion = 6;
    cout << firstBadVersion(7) << endl;
    badVersion = 4;
    cout << firstBadVersion(7) << endl;
    badVersion = 2;
    cout << firstBadVersion(7) << endl;
    badVersion = 1;
    cout << firstBadVersion(1) << endl;
    badVersion = 2;
    cout << firstBadVersion(2) << endl;
}