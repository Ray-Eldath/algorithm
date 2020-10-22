//
// Created by Ray Eldath on 2020/10/19.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

struct Queen {
    int m_x, m_y;

    explicit Queen(int x = 0, int y = 0) : m_x(x), m_y(y) {}

    bool operator==(const Queen &lhs) const {
        return m_x == lhs.m_x ||
               m_y == lhs.m_y ||
               m_x + m_y == lhs.m_x + lhs.m_y ||
               m_x - m_y == lhs.m_x - lhs.m_y;
    }

    bool operator!=(const Queen &lhs) const { return !(*this == lhs); }
};

vector<vector<string>> solveNQueens(int N) {
    vector<Queen> r;
    vector<vector<string>> solutions;
    auto q = Queen(0, 0);

    do {
        if (q.m_y >= N || r.size() >= N) {
            if (r.size() >= N) {
                vector<string> solution;
                for (auto tq:r) {
                    stringstream ss;
                    for (int i = 0; i < N; i++)
                        ss << ".";
                    auto line = ss.str();
                    line[tq.m_y] = 'Q';
                    solution.push_back(line);
                }
                solutions.push_back(solution);
            }
            q = r.back();
            r.pop_back();
            q.m_y++;
        } else {
            while (q.m_y < N && find(r.cbegin(), r.cend(), q) != r.cend())
                q.m_y++;

            if (q.m_y < N) {
                r.push_back(q);
                q.m_x++;
                q.m_y = 0;
            }
        }
    } while (!(q.m_x == 0 && q.m_y >= N));

    return solutions;
}

int main() {
    for (const auto &solution:solveNQueens(4)) {
        for (const auto &line:solution)
            cout << line << endl;
        cout << endl;
    }
}