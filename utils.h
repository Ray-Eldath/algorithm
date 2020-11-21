//
// Created by Ray Eldath on 2020/11/20.
//

#ifndef ALGORITHM_UTILS_H
#define ALGORITHM_UTILS_H

#endif //ALGORITHM_UTILS_H

#include <memory>

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args &&... args) { return std::unique_ptr<T>(new T(std::forward<Args>(args)...)); }