//
// Created by Ray Eldath on 2020/10/21.
//
#include "4.h"
#include <iostream>
#include <sstream>

using namespace std;

enum class Status {
    AVAILABLE, ON_ROUTE, BACKTRACKED, UNAVAILABLE
};

enum class Direction {
    UNKNOWN, RIGHT, DOWN, LEFT, UP, NO_WAY
};

struct Cell {
    int x = 0, y = 0;
    Status status = Status::UNAVAILABLE;
    Direction from = Direction::UNKNOWN, to = Direction::UNKNOWN;
    int remaining_to = 4;

    inline bool operator==(const Cell &rhs) const { return rhs.x == x && rhs.y == y; }
};

inline Cell *toNext(Cell *cell) {
    if (cell->remaining_to == 0)
        cell->to = Direction::NO_WAY;
    else if (cell->to == Direction::UNKNOWN) {
        srand(time(nullptr));
        cell->to = static_cast<Direction>(rand() % 4 + 1);
        cell->remaining_to--;
    } else {
        cell->to = static_cast<Direction>(static_cast<int>(cell->to) % 4 + 1);
        cell->remaining_to--;
    }
    return cell;
}

inline Direction alternate(Direction direction) {
    switch (direction) {
        case Direction::LEFT :
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        default:
            return Direction::UNKNOWN;
    }
}

inline Cell *neighbor(Cell **labyrinth, Cell *cell) {
    const auto x = cell->x, y = cell->y;
    switch (cell->to) {
        case Direction::RIGHT:
            return &labyrinth[x][y + 1];
        case Direction::DOWN :
            return &labyrinth[x + 1][y];
        case Direction::LEFT :
            return &labyrinth[x][y - 1];
        case Direction::UP :
            return &labyrinth[x - 1][y];
        default:
            return {};
    }
}

inline Cell *advance(Cell **labyrinth, Cell *cell) {
    Cell *next = neighbor(labyrinth, cell);
    next->from = alternate(cell->to);
    return next;
}

void print(Cell **labyrinth, int N, Cell &s_r, Cell &t_s);

Stack<Cell *> solveLabyrinth(Cell **labyrinth, const int N, Cell *s, Cell *t) {
    Stack<Cell *> path;
    s->status = Status::ON_ROUTE;
    path.push(s);
    do {
        print(labyrinth, N, *s, *t);

        Cell *c = path.top();
        if (c == t) return path;
        while (toNext(c)->to != Direction::NO_WAY) { // toNext 将 c 的 to 置为下一个可用的方向（若有）
            if (neighbor(labyrinth, c)->status == Status::AVAILABLE) // 如果有可用的方向，检测该方向是否可通行
                break;
        }

        if (c->to == Direction::NO_WAY) { // 如果没有可通行的方向则回溯
            c->status = Status::BACKTRACKED;
            path.pop();
        } else {
            path.push(c = advance(labyrinth, c));
            c->to = Direction::UNKNOWN;
            c->status = Status::ON_ROUTE;
        }

    } while (!path.empty());

    return path;
}

inline bool checkDirection(const Direction &a, const Direction &b, const Direction &from, const Direction &to) {
    return (from == a && to == b) || (from == b && to == a);
}

void print(Cell **labyrinth, const int N, Cell &s_r, Cell &t_s) {
    stringstream ss;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            auto c = labyrinth[x][y];
            string cc = " ";

            auto cs = c.status;
            if (cs == Status::UNAVAILABLE)
                cc = "#";
            else if (cs == Status::ON_ROUTE) {
                auto from = c.from, to = c.to;

                if (checkDirection(Direction::LEFT, Direction::UP, from, to))
                    cc = "┘";
                else if (checkDirection(Direction::RIGHT, Direction::UP, from, to))
                    cc = "└";
                else if (checkDirection(Direction::LEFT, Direction::DOWN, from, to))
                    cc = "┐";
                else if (checkDirection(Direction::RIGHT, Direction::DOWN, from, to))
                    cc = "┌";

                else if (checkDirection(Direction::LEFT, Direction::RIGHT, from, to))
                    cc = '-';
                else if (checkDirection(Direction::UP, Direction::DOWN, from, to))
                    cc = '|';
                else
                    cc = '*';
            }

            if (c == s_r)
                cc = '+';
            else if (c == t_s)
                cc = '-';

            ss << cc;
        }
        ss << endl;
    }

    cout << ss.str();
}

void convert(const string &labyrinth, int N, Cell **labyrinth_s, Cell *&s_r, Cell *&t_s) {
    stringstream f(labyrinth);
    string line;

    int x = 0;
    while (getline(f, line)) {
        if (line.size() != N)
            continue;
        for (size_t y = 0; y < line.size(); y++) {
            auto c = &labyrinth_s[x][y];
            c->x = x;
            c->y = y;

            auto cc = line[y];
            c->status = cc == '#' ? Status::UNAVAILABLE : Status::AVAILABLE;

            if (cc == '+')
                s_r = c;
            else if (cc == '-')
                t_s = c;
        }
        x++;
    }
}

void test(const int N, const string &labyrinth_s) {
    Cell **labyrinth = new Cell *[N];
    Cell *buffer = new Cell[N * N];
    for (int i = 0; i < N; i++)
        labyrinth[i] = buffer + i * N;

    Cell *s, *t;
    convert(labyrinth_s, N, labyrinth, s, t);
    cout << (solveLabyrinth(labyrinth, N, s, t).empty() ? "insoluble" : "solvable") << endl;
    cout << endl;
    delete[] buffer;
    delete[] labyrinth;
}

int main() {

    test(8, R"(
########
#   #  #
# #   ##
### #  #
#+  # ##
#   # -#
#   #  #
########
)");

    test(6, R"(
######
#+ # #
#  #-#
# # ##
#    #
######
)");

    test(8, R"(
########
#+     #
#      #
#      #
#      #
#      #
#     -#
########
)");

}