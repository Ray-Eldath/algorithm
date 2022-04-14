//
// Created by ray-eldath on 2022/4/11.
//
#include "utils.h"

using namespace std;

string reverseWords(string s) {
    int i = 0, j = 0;
    while (i < s.size() && j < s.size()) {
        if (j == s.size() - 1 || s[j + 1] == ' ') {
            int k = j;
//            cout << "1: " << i << " " << k << endl;
            while (i < k) {
                char c = s[k];
                s[k] = s[i];
                s[i] = c;
                i++;
                k--;
            }
            i = j + 2;
//            cout << "2: " << i << " " << j << endl;
        }
        j++;
    }
    return s;
}

string reverseWords2(string s) {
    int i = 0, j = 0;
    while (i < s.size()) {
        bool b = j == s.size() - 1;
        if (s[j] == ' ' || b) {
            int k = b ? j : j - 1;
//            cout << "1: " << i << " " << k << endl;
            while (i < k) {
                char c = s[k];
                s[k] = s[i];
                s[i] = c;
                i++;
                k--;
            }
            i = j + 1;
//            cout << "2: " << i << " " << j << endl;
        }
        j++;
    }
    return s;
}

void test(const string &s) {
    cout << reverseWords(s) << endl;
    cout << reverseWords2(s) << endl;
}

int main() {
    test("");
    test("a");
    test("ab");
    test("abc");
    test("abc abc");
    test("Let's take LeetCode contest");
    test("God Ding");
}