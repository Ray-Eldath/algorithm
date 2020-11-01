//
// Created by Ray Eldath on 2020/11/1.
//
#include <string>
#include <iostream>

using namespace std;

struct TrieNode {
    TrieNode **next;
    bool terminal;

    explicit TrieNode(bool t = false) : terminal(t) { next = new TrieNode *[26]{nullptr}; }

    inline void insert_at(int pos, TrieNode *node) const { next[pos] = node; }
};

class Trie {
private:
    TrieNode *root = new TrieNode;

public:
    Trie() = default;

    void insert(const string &word) {
        auto c = root;
        for (auto ch : word) {
            auto node = c->next[ch - 'a'];
            if (node == nullptr)
                node = new TrieNode();
            c->insert_at(ch - 'a', node);
            c = node;
        }
        c->terminal = true;

//        auto c = root;
//        for (auto i = 0; i < word.size(); i++) {
//            auto node = c->next[word[i] - 'a'];
//            auto terminal = i == word.size() - 1;
//            if (node == nullptr || terminal)
//                node = new TrieNode(terminal);
//            c->insert_at(word[i] - 'a', node);
//            c = node;
//        }
    }

    bool search(const string &word) {
        auto c = root;
        for (char i : word) {
            auto node = c->next[i - 'a'];
            if (node == nullptr)
                return false;
            c = node;
        }

        return c->terminal;
    }

    bool startsWith(const string &prefix) {
        auto c = root;
        for (auto ch:prefix) {
            auto node = c->next[ch - 'a'];
            if (node == nullptr)
                return false;
            c = node;
        }

        return true;
    }
};

int main() {
    auto trie = new Trie;
    for (const auto &xx:{"jow", "ae", "aaa", "bb", "xyz"})
        trie->insert(xx);
    trie->insert("xy");
    for (const auto &xx:{"jow", "jo", "ae", "aa", "bb", "b", "xyz", "xy", ""})
        cout << trie->search(xx) << " " << trie->startsWith(xx) << endl;
}