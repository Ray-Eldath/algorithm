//
// Created by Ray Eldath on 2020/11/2.
//

#ifndef ALGORITHM_6_H
#define ALGORITHM_6_H

#endif //ALGORITHM_6_H

#include <climits>
#include <queue>
#include <vector>
#include <functional>
#include <iostream>
#include <stack>

enum class VertexStatus {
    UNDISCOVERED, DISCOVERED, VISITED
};

enum class EdgeType {
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
};

template<typename Tv>
struct Vertex {
    Tv data;
    int in_degree, out_degree;
    VertexStatus status;
    int priority;
    int d_time, f_time;
    int parent;

    explicit Vertex(const Tv &d = Tv()) : data(d), in_degree(0), out_degree(0),
                                          status(VertexStatus::UNDISCOVERED),
                                          priority(INT_MAX) {}
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
    bool m_digraph;

    void insert_edge__(const Te &data, int i, int j, int w = INT_MAX) {
        E[i][j] = new Edge<Te>(data, w);
        m_e++;
        out_degree(i)++;
        in_degree(j)++;
    }

public:
    explicit GraphMatrix(bool digraph = true) {
        m_n = m_e = 0;
        m_digraph = digraph;
    }

    ~GraphMatrix() {
        for (auto &r : E)
            for (auto &v : r)
                delete v;
    }

    inline int n() { return m_n; }

    inline int e() { return m_e; }

    inline Vertex<Tv> &vertex(int i) { return V[i]; }

    inline int &parent(int i) { return V[i].parent; }

    inline int &in_degree(int i) { return V[i].in_degree; }

    inline int &out_degree(int i) { return V[i].out_degree; }

    inline int &d_time(int i) { return V[i].d_time; }

    inline int &f_time(int i) { return V[i].f_time; }

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
        auto tv = vertex(i).data;
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

    Edge<Te> *edge(int i, int j) { return E[i][j]; }

    int &weight(int i, int j) { return E[i][j]->weight; }

    void insert_edge(const Te &data, int i, int j, int w = INT_MAX) {
        if (!m_digraph)
            insert_edge__(data, j, i, w);
        insert_edge__(data, i, j, w);
    }

    Te remove_edge(int i, int j) {
        Te e = edge(i, j)->data;
        delete E[i][j];
        E[i][j] = nullptr;
        m_e--;
        out_degree(i)--;
        in_degree(j)--;
        return e;
    }

    using VertexVisitor = std::function<void(Vertex<Tv> &)>;
    using EdgeVisitor = std::function<void(Edge<Te> &)>;

    void BFS(int v, VertexVisitor vertex_visitor, EdgeVisitor edge_visitor = [](Edge<Te> &e) {}) {
        std::queue<int> Q;
        status(v) = VertexStatus::DISCOVERED;
        Q.push(v);

        while (!Q.empty()) {
            auto c = Q.front();
            Q.pop();

            for (auto u = first_nbr(c); u > -1; u = next_nbr(c, u)) {
                if (status(u) == VertexStatus::UNDISCOVERED) {
                    status(u) = VertexStatus::DISCOVERED;
                    Q.push(u);
                    type(c, u) = EdgeType::TREE;
                } else
                    type(c, u) = EdgeType::CROSS;
                edge_visitor(*edge(c, u));
            }

            vertex_visitor(vertex(c));
            status(c) = VertexStatus::VISITED;
        }
    }

    void DFS(int v, int clock, VertexVisitor vertex_visitor, EdgeVisitor edge_visitor = [](Edge<Te> &e) {}) {
        d_time(v) = ++clock;
        status(v) = VertexStatus::DISCOVERED;

        for (auto u = first_nbr(v); u > -1; u = next_nbr(u, v)) {
            auto s = status(u);
            if (s == VertexStatus::UNDISCOVERED) {
                type(v, u) = EdgeType::TREE;
                DFS(u, clock, vertex_visitor, edge_visitor);
            } else if (s == VertexStatus::DISCOVERED)
                type(v, u) = EdgeType::BACKWARD;
            else type(v, u) = d_time(v) > d_time(u) ? EdgeType::CROSS : EdgeType::FORWARD;
        }


        status(v) = VertexStatus::VISITED;
        f_time(v) = ++clock;
    }

    void DFS_iterate(int v, VertexVisitor vertex_visitor, EdgeVisitor edge_visitor = [](Edge<Te> &e) {}) {
        int clock = 0;
        std::stack<int> S;
        status(v) = VertexStatus::DISCOVERED;
        d_time(v) = 0;
        S.push(v);

        auto t = m_n;
        while (!S.empty()) {
            auto c = S.top();

            auto u = next_nbr(c, t);
            if (u < 0) {
                vertex_visitor(vertex(c));
                S.pop();
                status(c) = VertexStatus::VISITED;
                f_time(c) = ++clock;
                t = c;
            } else {
                auto us = status(u);
                if (us == VertexStatus::UNDISCOVERED) {
                    type(c, u) = EdgeType::TREE;
                    status(u) = VertexStatus::DISCOVERED;
                    d_time(u) = ++clock;
                    S.push(u);
                    t = m_n;
                } else if (us == VertexStatus::DISCOVERED) {
                    type(c, u) = EdgeType::BACKWARD;
                    t = u;
                } else {
                    type(c, u) = d_time(c) < d_time(u) ? EdgeType::FORWARD : EdgeType::CROSS;
                    t = u;
                }

                edge_visitor(*edge(c, u));
            }
        }
    }

    std::vector<int> topological_sort() {
        std::vector<int> S, R;
        for (auto i = 0; i < m_n; i++)
            if (vertex(i).in_degree == 0)
                S.push_back(i);

        while (!S.empty()) {
            auto c = S.back();
            S.pop_back();

            for (auto u = first_nbr(c); u > -1; u = next_nbr(c, u)) {
                auto v = vertex(u);
                if (!(v.in_degree == 0 && v.out_degree == 0) && v.in_degree <= 1)
                    S.push_back(u);
                remove_edge(c, u);
            }
            R.push_back(c);
        }

        return R;

//        std::vector<int> R;
//        for (auto i = 0; i < m_n; i++)
//            if (vertex(i).in_degree == 0)
//                R.push_back(i);
//
//        int t = R.size() - 1;
//        while (t >= 0) {
//            auto c = R[t];
//            auto found = false;
//            for (auto u = first_nbr(c); u > -1; u = next_nbr(c, u)) {
//                auto v = vertex(u);
//                if (!(v.in_degree == 0 && v.out_degree == 0) && v.in_degree <= 1) { // 若存在该节点且仅有当前节点指向它
//                    std::cout << u << std::endl;
//                    R.push_back(u);
//                    found = true;
//                }
//                std::cout << c << "->" << u << std::endl;
//                remove_edge(c, u);
//            }
//
//            t = found ? R.size() - 1 : t - 1;
//        }
//
//        return R;
    }

#define hca(x) (f_time(x))

    void bcc(int v, int &clock, std::vector<int> &r) {
        hca(v) = d_time(v) = ++clock;
        status(v) = VertexStatus::DISCOVERED;

        for (auto u = first_nbr(v); u > -1; u = next_nbr(v, u)) {
            auto s = status(u);
            if (s == VertexStatus::UNDISCOVERED) {
                parent(u) = v;
                bcc(u, clock, r);

                if (hca(u) < d_time(v)) // 如果子节点能够访问比当前节点更高的节点，那么
                    hca(v) = std::min(hca(v), hca(u)); // “向上传递”子节点的hca
                else
                    r.push_back(v); // 否则，当前节点就是一个关节点
            } else if (s == VertexStatus::DISCOVERED && u != parent(v))
                hca(v) = std::min(hca(v), d_time(u));
        }
    }

    std::vector<int> BCC(int v) {
        int clock = 0;
        std::vector<int> r;
        bcc(v, clock, r);
        r.erase(r.end() - 1);

        return r;
    }
};