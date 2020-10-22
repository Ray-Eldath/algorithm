//
// Created by Ray Eldath on 2020/9/25.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

inline bool calLine(int o0, int o1, int o2, int x, int y) {
    return o0 + o1 * x + o2 * y > 0;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> A, B;

    for (int i = 0; i < n; i++) {
        int x, y;
        char t;
        cin >> x >> y >> t;
        if (t == 'A')
            A.emplace_back(make_pair(x, y));
        else if (t == 'B')
            B.emplace_back(make_pair(x, y));
    }

    for (int i = 0; i < m; i++) {
        int o0, o1, o2;
        cin >> o0 >> o1 >> o2;
        if (calLine(o0, o1, o2, A[0].first, A[0].second)) {
            if (
                    all_of(A.cbegin(), A.cend(), [&](pair<int, int> p) {
                        return calLine(o0, o1, o2, p.first, p.second);
                    }) && all_of(B.cbegin(), B.cend(), [&](pair<int, int> p) {
                        return !calLine(o0, o1, o2, p.first, p.second);
                    }))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        } else {
            if (
                    all_of(A.cbegin(), A.cend(), [&](pair<int, int> p) {
                        return !calLine(o0, o1, o2, p.first, p.second);
                    }) && all_of(B.cbegin(), B.cend(), [&](pair<int, int> p) {
                        return calLine(o0, o1, o2, p.first, p.second);
                    }))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    }
}