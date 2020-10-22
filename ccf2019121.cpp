#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int n, j = 0;
    int m[4] = {0};
    cin >> n;
    for (int i = 1; i <= n; i++) {
        stringstream ss;
        ss << i;
        string s;
        ss >> s;
        bool a = false;
        for (auto c: s)
            if (c == '7')
                a = true;
        if (i % 7 == 0 || a) {
            m[j]++;
            n++;
        }

//        cout << j << ":" << i << " ";

        j++;
        if (j == 4) {
            j = 0;
//            cout << endl;
        }
    }
    for (auto i : m) {
        cout << i << endl;
    }
    return 0;
}