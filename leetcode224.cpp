//
// Created by Ray Eldath on 2020/10/18.
//
#include <stack>
#include <string>
#include <iostream>

using namespace std;

char priority[7][7] = {
//           +    -    *    /    (    )   EOE
/* + */     '>', '>', '<', '<', '<', '>', '>',
/* - */     '>', '>', '<', '<', '<', '>', '>',
/* * */     '>', '>', '>', '>', '<', '>', '>',
/* / */     '>', '>', '>', '>', '<', '>', '>',
/* ( */     '<', '<', '<', '<', '<', '=', ' ',
/* ) */     ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/*EOE*/     '<', '<', '<', '<', '<', ' ', '=',
};

int char2num(char c) {
    switch (c) {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '(':
            return 4;
        case ')':
            return 5;
        case '\0':
            return 6;
        default:
            return -1;
    }
}

inline char comparePriority(char a, char b) { return priority[char2num(a)][char2num(b)]; }

inline int calc(int a, char op, int b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}

int calculate(const string &expression) {
    stack<int> operands;
    stack<char> operators;
    operators.push('\0');
    int c = 0;
    while (!operators.empty()) {
        auto current = expression[c];
        if (current == ' ') {
            c++;
            continue;
        }

        if (isdigit(current)) {
            auto ct = c;
            for (; isdigit(expression[c]); c++);
            operands.push(atoi(expression.substr(ct, c - ct).data()));
        } else {
            auto p = comparePriority(operators.top(), current);
            if (p == '<') {
                operators.push(current);
                c++;
            } else if (p == '>') {
                auto o1 = operands.top();
                operands.pop();
                auto o2 = operands.top();
                operands.pop();
                auto op = operators.top();
                operators.pop();

                operands.push(calc(o2, op, o1));
            } else if (p == '=') {
                operators.pop();
                c++;
            }
        }
    }

    return operands.top();
}

int main() {
    cout << calculate("1+3+5") << endl;
    cout << calculate("3*(((3+5)))/3") << endl;
}
