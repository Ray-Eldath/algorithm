//
// Created by Ray Eldath on 2020/10/16.
//
#include "4.h"
#include <sstream>

using namespace std;

const auto operator_count = 7;
enum class Operator {
    ADD, SUB, MUL, DIV, L_P, R_P, EOE, INVALID
};

char priority[operator_count][operator_count] = {
//             +    -    *    /    (    )   EOE
/*  +  */     '>', '>', '<', '<', '<', '>', '>',
/*  -  */     '>', '>', '<', '<', '<', '>', '>',
/*  *  */     '>', '>', '>', '>', '<', '>', '>',
/*  /  */     '>', '>', '>', '>', '<', '>', '>',
/*  (  */     '<', '<', '<', '<', '<', '=', ' ',
/*  )  */     ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/* EOE */     '<', '<', '<', '<', '<', ' ', '=',
};

Operator char2enum(char c) {
    if (c == '+')
        return Operator::ADD;
    else if (c == '-')
        return Operator::SUB;
    else if (c == '*')
        return Operator::MUL;
    else if (c == '/')
        return Operator::DIV;
    else if (c == '(')
        return Operator::L_P;
    else if (c == ')')
        return Operator::R_P;
    else if (c == '\0')
        return Operator::EOE;
    else
        return Operator::INVALID;
}

char checkPriority(char top, char cur) {
    auto r = priority[static_cast<int>(char2enum(top))][static_cast<int>(char2enum(cur))];
//    cout << "check at: [" << static_cast<int>(char2enum(top)) << "]" <<
//         " [" << static_cast<int>(char2enum(cur)) << "]" <<
//         " -> " << r << endl;
    return r;
}

double calc(Operator op, double operand1, double operand2) {
    if (op == Operator::ADD)
        return operand1 + operand2;
    else if (op == Operator::SUB)
        return operand1 - operand2;
    else if (op == Operator::MUL)
        return operand1 * operand2;
    else if (op == Operator::DIV)
        return operand1 / operand2;
    else
        return 0.0;
}

double readNum(const string &str) {
    double r = 0.0, x = 1;
    int m = str.size();
    for (auto i = 0; i < str.size(); i++)
        if (str[i] == '.')
            m = i;
    for (auto i = m - 1; i >= 0; i--) {
        r += (str[i] - '0') * x;
        x *= 10;
    }
    x = 0.1;
    for (auto i = m + 1; i < str.size(); i++) {
        r += (str[i] - '0') * x;
        x *= 0.1;
    }
    return r;
}

double calculate(const string &expression, stringstream &rpn) {
    Stack<char> operators;
    Stack<double> operands;
    operators.push('\0');

    int c = 0, lp = 0;
    while (!operators.empty()) {
        auto current = expression[c];

        if (isdigit(current)) {
            int ct = c;
            for (; isdigit(expression[c]) || expression[c] == '.'; c++);
            auto num = readNum(expression.substr(ct, c - ct));
            operands.push(num);
            rpn << num;
            rpn << " ";
        } else {
            char p = checkPriority(operators.top(), current);
            if (p == '<') {
                if (char2enum(current) == Operator::L_P)
                    lp++;
                if (operators.size() - lp != operands.size())
                    throw std::invalid_argument("unfinished term at " + to_string(c));
                operators.push(current);
                c++;
            } else if (p == '>') {
                if (operands.size() < 2)
                    throw std::invalid_argument("unfinished term at " + to_string(c));
                auto o1 = operands.pop(), o2 = operands.pop();
                auto op = operators.pop();
                operands.push(calc(char2enum(op), o2, o1));
                rpn << op;
                rpn << " ";
//                if (current != '\0')
//                    operators.push(current);
            } else if (p == '=') {
                operators.pop();
                c++;
            } else
                throw std::invalid_argument("unmatched parentheses at " + to_string(c));
        }
    }
    return operands.pop();
}

void show(const string &expression) {
    try {
        stringstream rpn;
        cout << expression << "=" << calculate(expression, rpn) << endl;
        cout << '\t' << rpn.str() << endl;
    } catch (const invalid_argument &exception) {
        cout << "failed" << endl << '\t' << exception.what() << endl;
    }
}

int main() {
    readNum("13");

    show("123.12+27"); // 150.12
    show("123.12-56"); // 67.12
    show("123.12+13-56"); // 80.12
    show("123.12+(13-56)"); // 80.12
    show("14.34-2.5*2"); // 9.34
    show("4.35*((3.5+1.5))"); // 21.75

    show("2+8+7++6");
    show("2+8+7**6");
    show("2+8+((7+6)))");
    show("2+8+(((7+6))");
}