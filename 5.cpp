//
// Created by Ray Eldath on 2020/10/23.
//
#include "5.h"

using namespace std;

int main() {
    auto tree = new BinTree<char>;

    tree->emplace_root('i');
    auto d = tree->emplace_left(tree->root(), 'd');
    auto c = tree->emplace_left(d, 'c');
    auto a = tree->emplace_left(c, 'a');
    auto b = tree->emplace_right(a, 'b');
    auto h = tree->emplace_right(d, 'h');
    auto f = tree->emplace_left(h, 'f');
    tree->emplace_left(f, 'e');
    tree->emplace_right(f, 'g');

    auto l = tree->emplace_right(tree->root(), 'l');
    auto k = tree->emplace_left(l, 'k');
    tree->emplace_left(k, 'j');
    auto n = tree->emplace_right(l, 'n');
    tree->emplace_left(n, 'm');
    auto p = tree->emplace_right(n, 'p');
    tree->emplace_left(p, 'o');

    auto visitor = [](char c) { cout << c << " "; };
    tree->traverse_preorder_iterate(tree->root(), visitor);
    cout << endl;
//    tree->traverse_inorder_recursive(tree->root(), visitor);
//    cout << endl;
    tree->traverse_inorder_iterate(tree->root(), visitor);
    cout << endl;
    tree->traverse_inorder_iterate_compact(tree->root(), visitor);
    cout << endl;
    tree->traverse_postorder_iterate(tree->root(), visitor);
    cout << endl;
    tree->traverse_levelorder(tree->root(), visitor);
    cout << endl;

    cout << a->succ()->data << " " <<
         b->succ()->data << " " <<
         p->succ() << endl;

    delete tree;
}