//
// Created by Ray Eldath on 2020/10/6.
//

#ifndef ALGORITHM_2_34_H
#define ALGORITHM_2_34_H

#endif //ALGORITHM_2_34_H

#include <memory>
#include <cmath>
#include <memory.h>

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args &&... args) { return std::unique_ptr<T>(new T(std::forward<Args>(args)...)); }

class Bitmap {
private:
    long *F, N, *T, top;

    inline void init(long s) {
        N = s;
        F = new long[N];
        T = new long[N];
    }

    void expand() {
        if (top < N)
            return;
        auto oldN = N;
        auto oldF = F, oldT = T;
        init(2 * oldN);

        const auto ss = oldN * sizeof(long);
        memcpy(F, oldF, ss);
        memcpy(T, oldT, ss);

        delete[] oldF;
        delete[] oldT;
    }

    inline bool valid(long i) const { return i >= 0 && i < N; }

public:
    explicit Bitmap(long s = 255) { init(s); }

    ~Bitmap() noexcept {
        delete[] F;
        delete[] T;
    };

    void set(long i) {
        if (!valid(i)) return;
        expand();
        if (i != labs(F[i]))
            F[i] = top++;
        T[F[i]] = i;
    }

    inline void clear(long i) { T[F[i]] = -i; }

    inline bool test(long i) const { return valid(i) && T[F[i]] == i; }

    inline bool operator[](long i) const { return test(i); }
};
