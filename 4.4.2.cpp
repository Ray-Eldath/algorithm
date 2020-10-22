//
// Created by Ray Eldath on 2020/10/19.
//
#include <sstream>
#include "4.h"

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

    explicit operator string() const {
        stringstream ss;
        ss << "(" << m_x << ", " << m_y << ")";
        return ss.str();
    }
};

int queen(int N) {
    Stack<Queen> r;
    int solutions = 0;

    auto q = Queen(0, 0);
    do {
        if (q.m_y >= N || r.size() >= N) { // 在上一次放置已越界，或上一次尝试已放满时回溯
            if (r.size() >= N)
                solutions++;
//            auto tq = q;
//            cout << "pre-pop: " << static_cast<string>(tq) << endl;
            q = r.pop();
//            cout << "popped: " << static_cast<string>(q) << endl;
            q.m_y++;
        } else {
            while (q.m_y < N && r.find(q) != r.end()) { // 如果当前放置未越界且有冲突
//                auto qq = r.find(q);
//                cout << "conflict with " << qq << " end: " << r.end() << endl;
                q.m_y++; // 尝试放置在下一列
            }

            if (q.m_y < N) { // 若未越界
                r.push(Queen(q.m_x, q.m_y));
                q.m_x++;
                q.m_y = 0;
            }
        }
    } while (!(q.m_x == 0 && q.m_y >= N)); // 当连第一个放置都已经越界时结束

    return solutions;
}

int main() {
    cout << queen(4) << endl;
}