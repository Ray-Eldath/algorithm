//
// Created by Ray Eldath on 2020/11/9.
//
#include "6.h"
#include <unordered_map>

using namespace std;

struct LeveledNode {
    int id;
    int level;
};

template<typename Tv, typename Te>
unordered_map<Tv, int> shortest_path(GraphMatrix<Tv, Te> *gm, int s) {
    queue<LeveledNode> Q;
    gm->status(s) = VertexStatus::DISCOVERED;
    Q.push(LeveledNode{s, 0});

    unordered_map<Tv, int> R;
    while (!Q.empty()) {
        auto c = Q.front();
        Q.pop();

        for (auto u = gm->first_nbr(c.id); u > -1; u = gm->next_nbr(c.id, u)) {
            if (gm->status(u) == VertexStatus::UNDISCOVERED) {
                gm->status(u) = VertexStatus::DISCOVERED;
                auto cl = c.level + 1;
                Q.push(LeveledNode{u, cl});
                R.insert(make_pair(gm->vertex(u).data, cl));
            }
        }

        gm->status(c.id) = VertexStatus::VISITED;
    }

    return R;
}

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

    for (auto &pair: shortest_path(gm, 0))
        cout << pair.first << " " << pair.second << endl;

    delete gm;
}