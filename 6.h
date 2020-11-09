//
// Created by Ray Eldath on 2020/11/2.
//

#ifndef ALGORITHM_6_H
#define ALGORITHM_6_H

#endif //ALGORITHM_6_H

#include <climits>
#include <queue>
#include <functional>
#include <iostream>

enum class VertexStatus {
    UNDISCOVERED, DISCOVERED, VISITED
};

enum class EdgeType {
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
};

template<typename Tv>
struct Vertex {
    Tv data;
    int in_degree, out_degree, parent;
    VertexStatus status;
    int priority;

    explicit Vertex(const Tv &d = Tv()) : data(d), in_degree(0), out_degree(0),
                                          status(VertexStatus::UNDISCOVERED),
                                          parent(0), priority(INT_MAX) {}
};

template<typename Te>
struct Edge {
    Te data;
    int weight;
    EdgeType type;

    explicit Edge(const Te &d, int w) : data(d), weight(w), type(EdgeType::UNDETERMINED) {}
};

template<typename Tv, typename Te>
class GraphMatrix {
private:
    using edge_iterator = Edge<Te> *;

    std::vector<Vertex<Tv>> V;
    std::vector<std::vector<edge_iterator>> E;

    int m_n, m_e;

public:
    explicit GraphMatrix() { m_n = m_e = 0; }

    ~GraphMatrix() {
        for (auto &r : E)
            for (auto &v : r)
                delete v;
    }

    inline int n() { return m_n; }

    inline int e() { return m_e; }

    inline Tv &vertex(int i) { return V[i].data; }

    inline int &in_degree(int i) { return V[i].in_degree; }

    inline int &out_degree(int i) { return V[i].out_degree; }

    inline int first_nbr(int i) { return next_nbr(i, m_n); }

    inline int next_nbr(int i, int j) { // 我草，我是真的服了，这里一开始是个 size_t，然后我debug了一个上午。。。。。。
        while (j > -1 && !exists(i, --j));
        return j;
    }

    inline VertexStatus &status(int i) { return V[i].status; }

    inline int &priority(int i) { return V[i].priority; }

    inline bool exists(int i, int j) {
//        auto t = i >= 0 && i < m_n && j >= 0 && j < m_n && E[i][j] != nullptr;
//        std::cout << "i=" << i << " j=" << j << " " << t << std::endl;
        return i >= 0 && i < m_n && j >= 0 && j < m_n && E[i][j] != nullptr;
    }

    int insert_vertex(const Tv &vertex) {
        for (auto &row : E) row.push_back(nullptr);
        m_n++;
        E.emplace_back(std::vector<edge_iterator>(m_n, nullptr));
        V.emplace_back(Vertex<Tv>(vertex));
        return m_n;
    }

    Tv remove_vertex(int i) {
        for (auto j = 0; j < m_n; i++)
            if (exists(i, j)) {
                delete E[i][j];
                in_degree(j)--;
            }

        E.erase(E.cbegin() + i - 1);
        m_n--;
        auto tv = vertex(i);
        V.erase(V.cbegin() + i - 1);

        for (auto j = 0; j < m_n; j++) {
            if (auto e = *E[j].erase(E[j].cbegin() + i)) {
                delete e;
                out_degree(j)--;
            }
        }
        return tv;
    }

    EdgeType &type(int i, int j) { return E[i][j]->type; }

    Te &edge(int i, int j) { return E[i][j]->data; }

    int &weight(int i, int j) { return E[i][j]->weight; }

    void insert_edge(const Te &data, int i, int j, int w = INT_MAX) {
        E[i][j] = new Edge<Te>(data, w);
        m_e++;
        out_degree(i)++;
        in_degree(j)++;
    }

    Te remove_edge(int i, int j) {
        Te e = edge(i, j);
        delete E[i][j];
        E[i][j] = nullptr;
        m_e--;
        in_degree(i)--;
        return e;
    }

    using VertexVisitor = std::function<void(Tv)>;
    using EdgeVisitor = std::function<void(Te)>;

    void BFS(int v, VertexVisitor vertex_visitor, EdgeVisitor edge_visitor = [](Te e) {}) {
        std::queue<int> Q;
        status(v) = VertexStatus::DISCOVERED;
        Q.push(v);

        while (!Q.empty()) {
            auto c = Q.front();
            Q.pop();

            for (auto u = first_nbr(c); u > -1; u = next_nbr(c, u)) {
                edge_visitor(edge(c, u));
                if (status(u) == VertexStatus::UNDISCOVERED) {
                    status(u) = VertexStatus::DISCOVERED;
                    Q.push(u);
                    type(c, u) = EdgeType::TREE;
                } else
                    type(c, u) = EdgeType::CROSS;
            }

            vertex_visitor(vertex(c));
            status(c) = VertexStatus::VISITED;
        }
    }
};