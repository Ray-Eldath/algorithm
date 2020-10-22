//
// Created by Ray Eldath on 2020/10/22.
//
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "memory.h"

using namespace std;

struct Word {
    int i;
    int n;
};

bool wordBreak(const string &s, vector<string> &wordDict) {
    const int N = s.size();
    vector<Word> r;
    int memo[N];
    memset(memo, 0, N * sizeof(int));

    auto w = Word{0, 0};
    do {
        bool flag = !r.empty() && r.back().i + r.back().n >= N;
        if (w.i + w.n > N || flag) {
            if (flag)
                return true;
            w = r.back();
            r.pop_back();
            w.n++;
        } else {
            if (memo[w.i] != 0) // 如果已经扫过当前位置
                w.n = memo[w.i] + 1; // 直接跳过已经扫过的部分
            while (w.i + w.n <= N && find(wordDict.cbegin(), wordDict.cend(), s.substr(w.i, w.n)) == wordDict.cend()) {
//                cout << s.substr(w.i, w.n) << endl;
                w.n++;
            }

            if (w.i + w.n <= N) {
                r.push_back(Word{w.i, w.n});
                memo[w.i] = w.n; // 记忆已经扫过的部分
                w.i = r.back().i + r.back().n;
                w.n = 0;
            }
        }
    } while (!(w.i == 0 && w.n >= N - 1));

    return false;
}

void test(const string &str, initializer_list<string> dict) {
    vector<string> v(dict);
    cout << wordBreak(str, v) << endl;
}

int main() {
    test("applepenapple", {"apple", "pen"});
    test("catsanddog", {"cat", "cats", "sand", "and", "dog", "sanddog"});
    test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
         {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"});
}