//
// Created by Ray Eldath on 2020/11/2.
//

#ifndef ALGORITHM_6_H
#define ALGORITHM_6_H

#endif //ALGORITHM_6_H

#include <climits>
#include <vector>

enum class VertexStatus {
    UNDISCOVERED, DISCOVERED, VISITED
};

enum class EdgeType {
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
};

template<typename Tv>
struct Vertex {
    Tv data;
    size_t in_degree, out_degree, parent;
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

    size_t m_n, m_e;

public:
    explicit GraphMatrix() { m_n = m_e = 0; }

    ~GraphMatrix() {
        for (auto &r : E)
            for (auto &v : r)
                delete v;
    }

    inline size_t n() { return m_n; }

    inline size_t e() { return m_e; }

    inline Tv &vertex(size_t i) { return V[i].data; }

    inline size_t &in_degree(size_t i) { return V[i].in_degree; }

    inline size_t &out_degree(size_t i) { return V[i].out_degree; }

    inline size_t first_nbr(size_t i) { return next_nbr(i, m_n); }

    inline size_t next_nbr(size_t i, size_t j) {
        while (j > -1 && (!exists(j))) j--;
        return j;
    }

    inline VertexStatus &status(size_t i) { return V[i].status; }

    inline size_t &priority(size_t i) { return V[i].priority; }

    inline bool exists(size_t i, size_t j) { return i >= 0 && i < m_n && j >= 0 && j < m_n && E[i][j] != nullptr; }

    size_t insert(const Tv &vertex) {
        for (auto &row : E) row.push_back(nullptr);
        m_n++;
        E.emplace_back(std::vector<edge_iterator>{nullptr});
        V.emplace_back(Vertex<Tv>(vertex));
        return m_n;
    }

    Tv remove(size_t i) {
        for (auto j = 0; j < m_n; i++)
            if (exists(i, j)) {
                delete E[i][j];
                in_degree(j)--;
            }

        E.erase(E.cbegin() + i);
        m_n--;
        auto tv = vertex(i);
        V.erase(V.cbegin() + i);

        for (auto j = 0; j < m_n; j++) {
            if (auto e = *E[j].erase(E[j].cbegin() + i)) {
                delete e;
                out_degree(j)--;
            }
        }
        return tv;
    }

    EdgeType &type(size_t i, size_t j) { return E[i][j]->type; }

    Te &edge(size_t i, size_t j) { return E[i][j]->data; }

    int &weight(size_t i, size_t j) { return E[i][j]->weight; }

    void insert(const Te &edge, int w, size_t i, size_t j) {
        E[i][j] = new Edge<Te>(edge, w);
        m_e++;
        out_degree(i)++;
        in_degree(j)++;
    }

    Te remove(size_t i, size_t j) {
        Te e = edge(i, j);
        delete E[i][j];
        E[i][j] = nullptr;
        m_e--;
        in_degree(i)--;
        return e;
    }
};