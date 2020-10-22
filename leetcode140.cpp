//
// Created by Ray Eldath on 2020/10/21.
//
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "memory.h"

using namespace std;

struct Word {
    int i, n;
};

template<typename T>
inline T printWith(const T &t, const bool mute = false) {
    if (!mute)
        cout << t << endl;
    return t;
}

vector<string> wordBreak(string &s, vector<string> &wordDict) {
    int N = s.size();
    vector<Word> r;
    vector<string> solutions;
    int memo[N];
    memset(memo, 0, N * sizeof(int));
    sort(wordDict.begin(), wordDict.end());

    auto w = Word{0, 0};
    do {
        bool flag = !r.empty() && r.back().i + r.back().n >= N;
        if (w.i + w.n > N || flag) {
            if (flag) {
                stringstream ss;
                for (size_t i = 0; i < r.size(); i++) {
                    auto word = r[i];
                    ss << s.substr(word.i, word.n);
                    if (i < r.size() - 1)
                        ss << " ";
                }
//                cout << ss.str() << endl;
                solutions.push_back(ss.str());
                memset(memo, 0, N * sizeof(int));
            }
            w = r.back();
            r.pop_back();
            w.n++;
//            memo[w.i]--;
        } else {
            if (memo[w.i] != 0)
                w.n = memo[w.i] + 1;
            while (w.i + w.n <= N &&
                   !binary_search(wordDict.cbegin(), wordDict.cend(),
                                  printWith(s.substr(w.i, w.n), true))) {
//                cout << s.substr(w.i, w.n) << endl;
                w.n++;
            }

            if (w.i + w.n <= N) {
                r.push_back(Word{w.i, w.n});
                memo[w.i] = w.n;
                w.i = r.back().i + r.back().n;
                w.n = 0;
            }
        }
    } while (!(w.i == 0 && w.n >= N - 1));

    reverse(solutions.begin(), solutions.end());
//    sort(solutions.begin(), solutions.end());
    return solutions;
}

void test(string str, const initializer_list<string> dict, const bool mute = false) {
    vector<string> v(dict);
    for (const auto &s:wordBreak(str, v))
        if (!mute)
            cout << s << endl;
}

int main() {
    test("catsanddog", {"cat", "cats", "and", "sand", "dog"});
    test("pineapplepenapple", {"apple", "pen", "applepen", "pine", "pineapple"});
    test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
         {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"});
}