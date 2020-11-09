//
// Created by Ray Eldath on 2020/11/2.
//

#include "6.h"
#include <iostream>

using namespace std;

int main() {
    auto gm = new GraphMatrix<char, int>();
    gm->insert_vertex('S');
    for (auto c = 'A'; c <= 'G'; c++)
        gm->insert_vertex(c);

    gm->insert_edge(1, 0, 1);
    gm->insert_edge(2, 0, 3);
    gm->insert_edge(3, 0, 4);
    gm->insert_edge(4, 1, 3);
    gm->insert_edge(5, 1, 5);
    gm->insert_edge(6, 3, 2);
    gm->insert_edge(7, 4, 2);
    gm->insert_edge(8, 5, 7);
    gm->insert_edge(9, 5, 6);
    gm->insert_edge(10, 7, 6);
    gm->insert_edge(11, 7, 2);

    auto show_char = [](char c) { cout << c << endl; };
    auto show_int = [](int i) { cout << i << " "; };

//    cout << gm->exists(0, 3) << " " << gm->exists(0, 4) << " " << gm->exists(0, 7) << endl;

    gm->BFS(0, show_char, show_int);

    delete gm;
}