//
// Created by ray-eldath on 2022/4/14.
//
#include <string>
#include <iostream>

using namespace std;

int lengthOfLongestSubstring(string s) {
    int max, start, end;
    max = start = end = 0;
    for (char c: s) {
        for (int i = end - 1; i >= start; i--) {
            if (s[i] == c) {
                max = end - start > max ? end - start : max;
                start = i + 1;
                break;
            }
        }
        end++;
        for (int j = start; j < end; ++j)
            cout << s[j];
        cout << " ";
    }
    max = end - start > max ? end - start : max;
    cout << " s=" << start << " e=" << end << " ";
    return max;
}

int main() {
    cout << lengthOfLongestSubstring("") << endl; // 0
    cout << lengthOfLongestSubstring("bcbcde") << endl; // 4
    cout << lengthOfLongestSubstring("abcabcbb") << endl; // 3
    cout << lengthOfLongestSubstring("bbbbb") << endl; // 1
    cout << lengthOfLongestSubstring("pwwkew") << endl; // 3
    cout << lengthOfLongestSubstring("dvdf") << endl; // 3
    cout << lengthOfLongestSubstring("dvdvf") << endl; // 3
    cout << lengthOfLongestSubstring("dvdvff") << endl; // 3
}