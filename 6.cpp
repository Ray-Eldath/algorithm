//
// Created by Ray Eldath on 2020/11/2.
//

#include "6.h"
#include "utils.h"
#include <iostream>

using namespace std;

int main() {
    {
        auto gm = make_unique<GraphMatrix<char, int>>();
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

        auto show_char = [](Vertex<char> c) { cout << c.data << "-" << static_cast<int>(c.status) << endl; };
        auto show_int = [](Edge<int> i) { cout << i.data << "=" << static_cast<int>(i.type) << " "; };

//    cout << gm->exists(0, 3) << " " << gm->exists(0, 4) << " " << gm->exists(0, 7) << endl;

        gm->BFS(0, show_char, show_int);
    }
    cout << endl;

    {
        auto gm = make_unique<GraphMatrix<char, int>>();
        for (auto c = 'A'; c <= 'G'; c++)
            gm->insert_vertex(c);

        gm->insert_edge(1, 0, 1);
        gm->insert_edge(2, 1, 2);
        gm->insert_edge(3, 0, 2);
        gm->insert_edge(4, 0, 5);
        gm->insert_edge(5, 5, 6);
        gm->insert_edge(6, 6, 0);
        gm->insert_edge(7, 6, 2);
    }
    cout << endl;

    {
        auto gm = make_unique<GraphMatrix<char, int>>();
        for (auto c = 'A'; c <= 'G'; c++)
            gm->insert_vertex(c);

        gm->insert_edge(0, 0, 3);
        gm->insert_edge(0, 0, 2);
        gm->insert_edge(0, 1, 2);
        gm->insert_edge(0, 1, 6);
        gm->insert_edge(0, 2, 3);
        gm->insert_edge(0, 2, 4);
        gm->insert_edge(0, 2, 5);
        gm->insert_edge(0, 4, 5);
        gm->insert_edge(0, 6, 5);

        for (auto i: gm->topological_sort())
            cout << i << " ";
    }
    cout << endl;

    {
        auto gm = make_unique<GraphMatrix<char, int>>(false);
        for (auto c = 'A'; c <= 'J'; c++)
            gm->insert_vertex(c);

        gm->insert_edge(0, 0, 1);
        gm->insert_edge(0, 1, 2);
        gm->insert_edge(0, 2, 3);
        gm->insert_edge(0, 3, 4);
        gm->insert_edge(0, 4, 6);
        gm->insert_edge(0, 5, 6);
        gm->insert_edge(0, 3, 6);
        gm->insert_edge(0, 2, 7);
        gm->insert_edge(0, 0, 9);
        gm->insert_edge(0, 0, 8);
        gm->insert_edge(0, 0, 7);
        gm->insert_edge(0, 8, 9);

        for (auto e:gm->BCC(0))
            cout << gm->vertex(e).data << " ";
    }
    cout << endl;

    {
        auto gm = make_unique<GraphMatrix<char, int>>(false);
        for (auto c = 'A'; c <= 'G'; c++)
            gm->insert_vertex(c);

        gm->insert_edge(0, 0, 1);
        gm->insert_edge(0, 0, 2);
        gm->insert_edge(0, 1, 3);
        gm->insert_edge(0, 2, 3);
        gm->insert_edge(0, 3, 4);
        gm->insert_edge(0, 4, 5);
        gm->insert_edge(0, 5, 6);
        gm->insert_edge(0, 4, 6);

        for (auto e:gm->BCC(0))
            cout << gm->vertex(e).data << " ";
    }
}