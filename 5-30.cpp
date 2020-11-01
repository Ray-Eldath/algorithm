//
// Created by Ray Eldath on 2020/10/31.
//
#include <string>
#include <utility>
#include <iostream>

using namespace std;

const int N_CHARS = 26;

struct TrieNode {
    using iterator = TrieNode *;

    bool terminal;
    iterator *next;

    explicit TrieNode(bool t = false) : terminal(t) { next = new iterator[N_CHARS]; }

    ~TrieNode() { delete[] next; }

    iterator insert_at(int pos, iterator iter) const { return next[pos] = iter; }
};

class Trie {
private:
    using iterator = typename TrieNode::iterator;

    iterator root = new TrieNode;

public:
    Trie(initializer_list<string> strs) {
        for (const auto &str:strs) {
            auto c = root;
            for (auto i = 0; i < str.size(); i++) {
                auto node = c->next[str[i] - 'a'];
                auto terminal = i == str.size() - 1;
                if (node == nullptr || terminal)
                    node = new TrieNode(terminal);
                c->insert_at(str[i] - 'a', node);
                c = node;
            }
        }
    }

    bool search(const string &str) {
        auto c = root;
        for (auto i = 0; i < str.size(); i++) {
            auto node = c->next[str[i] - 'a'];
            if (node == nullptr || i == str.size() - 1 && !node->terminal)
                return false;
            else
                c = node;
        }
        return true;
    }

    bool starts_with(const string &str) {
        auto c = root;
        for (auto ch:str) {
            iterator node = c->next[ch - 'a'];
            if (node == nullptr)
                return false;
            else
                c = node;
        }
        return true;
    }
};

int main() {
    auto trie = new Trie{"jow", "ae", "aaa", "bb", "xyz"};
    auto x = {"jow", "jo", "ae", "aa", "bb", "b", "xyz", "xy"};
    for (const auto &xx:x)
        cout << trie->search(xx) << " " << trie->starts_with(xx) << endl;
}