//
// Created by Ray Eldath on 2020/10/30.
//

#include "5.h"
#include <vector>
#include <fstream>
#include <map>

using namespace std;

struct HuffmanChar {
    char ch;
    double possibility;

    explicit HuffmanChar(double p = 0.0, char c = '\0') : ch(c), possibility(p) {}

    bool operator<(const HuffmanChar &rhs) const { return possibility < rhs.possibility; }
};

using HuffmanTree = BinTree<HuffmanChar>;
using HuffmanForest = vector<HuffmanTree *>;
using HuffmanTable = map<char, string>;

const char CHARS_START_AT = 32;
char N_CHARS = 0;

HuffmanForest generate_forest() {
    ifstream freqs_file("freq");
    if (freqs_file.is_open())
        cout << "freq file opened. generating forest..." << endl;

    vector<double> freqs;
    double freq_file;
    while (freqs_file >> freq_file)
        freqs.push_back(freq_file);

    HuffmanForest forest;
    char c = CHARS_START_AT;
    for (auto freq:freqs) {
        auto ht = new HuffmanTree();
        ht->emplace_root(*(new HuffmanChar(freq, c++)));
        forest.push_back(ht);
        N_CHARS++;
    }

    return forest;
}

HuffmanTree *find_smallest_char(HuffmanForest &forest) {
    auto pos = forest.cbegin();
    for (auto c = forest.cbegin(); c != forest.cend(); ++c)
        if ((*c)->root()->data < (*pos)->root()->data)
            pos = c;

    auto r = *pos;
    forest.erase(pos);
    return r;
}

HuffmanTree *generate_tree(HuffmanForest &forest) {
    while (forest.size() > 1) {
        auto t1 = find_smallest_char(forest);
        auto t2 = find_smallest_char(forest);

        auto s = new HuffmanTree;
        s->emplace_root(*(new HuffmanChar(t1->root()->data.possibility + t2->root()->data.possibility)));
        s->attach_left(s->root(), t1);
        s->attach_right(s->root(), t2);

        forest.push_back(s);
    }

    return forest[0];
}

void generate_table_item(const HuffmanTree::iterator &node, HuffmanTable &table, const string &str) {
    if (HuffmanTree::is_leaf(node)) {
        table.insert(make_pair(node->data.ch, str));
        return;
    }
    if (HuffmanTree::has_left(node)) // left -> 0
        generate_table_item(node->left, table, str + '0');
    if (HuffmanTree::has_right(node)) // right -> 1
        generate_table_item(node->right, table, str + '1');
}

HuffmanTable generate_table(const HuffmanTree &tree) {
    HuffmanTable table;
    generate_table_item(tree.root(), table, "");

    return table;
}

string encode(const string &input, HuffmanTable &table) {
    string r;
    for (const auto c:input)
        r += table.at(c);
    return r;
}

string decode(const string &input, HuffmanTree &tree) {
    int i = 0;
    string r;
    while (i < input.size()) {
        auto node = tree.root();
        while (!HuffmanTree::is_leaf(node)) {
            node = input[i] == '0' ? node->left : node->right;
            i++;
        }
        r += node->data.ch;
    }

    return r;
}

int main() {
    auto forest = generate_forest();
    for (auto i = forest.cbegin(); i < forest.cend(); i++) {
        auto data = (*i)->root()->data;
        cout << data.ch << " = " << data.possibility;
        if (i < forest.cend() - 1)
            cout << ", ";
    }
    cout << endl << endl;

    auto tree = generate_tree(forest);
    auto table = generate_table(*tree);
    cout << "generating encoding table..." << endl;
    for (const auto &item:table)
        cout << item.first << " = " << item.second << endl;

    cout << endl << "now testing encode & decode..." << endl;

    auto x = {
            "still love @capoo_jp @thecoronas and Nagisa Kaworu. // sci-fi, western literature :: jpop/jrock/acg, funk, drum, guitar :: programming // http://t.me/kaworunagisa17",
            "Seltsam, im Nebel zu wandern!",
            R"(# ProxyCommand C:\Users\Ray Eldath\scoop\apps\git\2.28.0.windows.1\mingw64\bin\connect.exe -S 127.0.0.1:1080 -a none %h %p)"};

    for (const auto &s:x) {
        cout << " -> origin: " << s << endl;
        auto e = encode(s, table);
        cout << " -> encoded: " << e << endl;
        auto d = decode(e, *tree);
        cout << " -> decoded: " << d << endl;
        cout << " --> " << (d == s ? "TRUE" : "FALSE") << endl << endl;
    }
}