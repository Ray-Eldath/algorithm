//
// Created by ray-eldath on 22-4-24.
//
#include "utils.h"

using namespace std;

void backtrack(int k, vector<int> &prefix, vector<int> &pos, string &s, vector<string> &result) {
    string r(s);
    for (auto p: prefix) r[p] ^= 32;
    result.emplace_back(r);

    for (int p = k; p < pos.size(); p++) {
        prefix.emplace_back(pos[p]);
        backtrack(p + 1, prefix, pos, s, result);
        prefix.pop_back();
    }
}

vector<string> letterCasePermutation(string s) {
    vector<int> prefix;
    vector<int> pos;
    vector<string> result;
    for (int i = 0; i < s.size(); i++) {
        if (isalpha(s[i]))
            pos.emplace_back(i);
    }
    backtrack(0, prefix, pos, s, result);
    return result;
}

int main() {
    printVector(letterCasePermutation("a1b2"));
    printVector(letterCasePermutation("x"));
    printVector(letterCasePermutation("3z4"));
}