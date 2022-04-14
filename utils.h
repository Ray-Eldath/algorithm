//
// Created by Ray Eldath on 2020/11/20.
//

#ifndef ALGORITHM_UTILS_H
#define ALGORITHM_UTILS_H

#endif //ALGORITHM_UTILS_H

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

template<typename F>
auto measure(F f) -> decltype(f()) {
    auto start = std::chrono::high_resolution_clock::now();
    auto r = f();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "[time: " << duration.count() << "ms] ";
    return r;
}