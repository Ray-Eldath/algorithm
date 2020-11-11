//
// Created by Ray Eldath on 2020/11/2.
//

#include "6.h"
#include <iostream>

using namespace std;

int main() {
    auto gm1 = new GraphMatrix<char, int>();
    gm1->insert_vertex('S');
    for (auto c = 'A'; c <= 'G'; c++)
        gm1->insert_vertex(c);

    gm1->insert_edge(1, 0, 1);
    gm1->insert_edge(2, 0, 3);
    gm1->insert_edge(3, 0, 4);
    gm1->insert_edge(4, 1, 3);
    gm1->insert_edge(5, 1, 5);
    gm1->insert_edge(6, 3, 2);
    gm1->insert_edge(7, 4, 2);
    gm1->insert_edge(8, 5, 7);
    gm1->insert_edge(9, 5, 6);
    gm1->insert_edge(10, 7, 6);
    gm1->insert_edge(11, 7, 2);

    auto show_char = [](Vertex<char> c) { cout << c.data << "=" << static_cast<int>(c.status) << endl; };
    auto show_int = [](Edge<int> i) { cout << i.data << "=" << static_cast<int>(i.type) << " "; };

//    cout << gm->exists(0, 3) << " " << gm->exists(0, 4) << " " << gm->exists(0, 7) << endl;

    gm1->BFS(0, show_char, show_int);

    delete gm1;
    cout << endl;

    auto gm2 = new GraphMatrix<char, int>();
    for (auto c = 'A'; c <= 'G'; c++)
        gm2->insert_vertex(c);

    gm2->insert_edge(1, 0, 1);
    gm2->insert_edge(2, 1, 2);
    gm2->insert_edge(3, 0, 2);
    gm2->insert_edge(4, 0, 5);
    gm2->insert_edge(5, 5, 6);
    gm2->insert_edge(6, 6, 0);
    gm2->insert_edge(7, 6, 2);

    gm2->DFS(0, show_char, show_int);
}