//
// Created by Ray Eldath on 2020/11/20.
//

#ifndef ALGORITHM_UTILS_H
#define ALGORITHM_UTILS_H

#include <vector>
#include <iostream>
#include <memory>
#include <chrono>

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args &&... args) { return std::unique_ptr<T>(new T(std::forward<Args>(args)...)); }

template<typename T>
void printVector(std::vector<T> ts) {
    for (const auto &item: ts)
        std::cout << item << " ";
    std::cout << std::endl;
}

template<typename T>
std::initializer_list<T> empty() {
    return std::initializer_list<T>{};
}

template<typename T, typename F>
void printInplaceVector(std::initializer_list<T> ts, F f) {
    std::vector<T> v{ts};
    f(v);
    printVector(v);
}

template<typename T>
void printDigits(std::vector<std::vector<T>> ts) {
    for (const auto &is: ts) {
        for (const auto &i: is)
            std::cout << i;
        std::cout << std::endl;
    }
}

template<typename T>
T removeConst(const T ts) {
    T rts(ts);
    return rts;
}

template<typename T, typename F_RETURN, typename F>
F_RETURN mapMatrixOf(std::initializer_list<std::initializer_list<T>> xs, F f) {
    std::vector<std::vector<T>> vs;
    for (const auto &item: xs) {
        std::vector<T> v{item};
        vs.emplace_back(v);
    }
    return f(vs);
}

template<typename F>
auto measure(F f) -> decltype(f()) {
    auto start = std::chrono::high_resolution_clock::now();
    auto r = f();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "[time: " << duration.count() << "ms] ";
    return r;
}

#endif //ALGORITHM_UTILS_H