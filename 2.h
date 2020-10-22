//
// Created by Ray Eldath on 2020/10/16.
//

#ifndef ALGORITHM_2_H
#define ALGORITHM_2_H

#endif //ALGORITHM_2_H

#include "2-34.h"

#include <memory>
#include <iostream>
#include <vector>
#include <functional>

template<typename T>
class Vector {
private:
    static const int DEFAULT_CAPACITY =
#ifdef DEBUG
            10
#else
    30
#endif
    ;

    using const_reference = const T &;
    using reference = T &;
    using const_iterator = const T *;
    using iterator = T *;

    size_t m_capacity, m_size;
    iterator m_elem;

protected:
    void expand() {
        if (m_size < m_capacity)
            return;
        if (m_capacity < DEFAULT_CAPACITY)
            m_capacity = DEFAULT_CAPACITY;
        auto newElem = new T[m_capacity <<= 1u];
        for (size_t i = 0; i < m_size; i++)
            newElem[i] = std::move_if_noexcept(m_elem[i]);
        delete[] m_elem;
        m_elem = newElem;
#ifdef DEBUG
        std::cout << "Vector expanded." << std::endl;
#endif
    }

public:
    explicit Vector(size_t s = 0, size_t c = DEFAULT_CAPACITY, T v = T()) {
        m_elem = new T[m_capacity = c];
        for (m_size = 0; m_size < s; m_elem[m_size++] = v);
    }

    Vector(const std::initializer_list<T> &elem) : Vector(elem.size()) {
        int i = 0;
        for (const auto &e:elem)
            insert(i++, e);
    }

    ~Vector() noexcept { delete[] m_elem; }

    inline reference operator[](size_t pos) const { return m_elem[pos]; }

    inline reference at(size_t pos) const { return operator[](pos); }

    inline iterator begin() const { return m_elem; }

    inline iterator end() const { return m_elem + m_size; }

    inline size_t size() const { return m_size; }

    inline bool empty() const { return size() == 0; }

    inline void swap(size_t l, size_t r) {
        auto ll = std::move(m_elem[l]);
        m_elem[l] = m_elem[r];
        m_elem[r] = std::move(ll);
    }

    size_t remove(size_t lo, size_t hi) {
        if (lo >= hi || lo < 0 || hi > m_size)
            return 0;
        while (hi < m_size)
            m_elem[lo++] = std::move_if_noexcept(m_elem[hi++]);
        m_size = lo;
        return hi - lo;
    }

    size_t remove(size_t pos) { return remove(pos, pos + 1); }

    size_t insert(size_t pos, const T e) {
        expand();
        for (size_t i = m_size; i > pos; i--)
            m_elem[i] = std::move_if_noexcept(m_elem[i - 1]);
        m_elem[pos] = std::move_if_noexcept(e);
        m_size++;
        return pos;
    }

    // [lo, hi)
    const_iterator find(const T &val, size_t lo, size_t hi) const {
        while (lo != hi && m_elem[lo] != val)
            ++lo;
        return m_elem + lo;

//        FAIL
//        for (size_t i = hi - 1; i >= lo; i--)
//            if (m_elem[i] == val)
//                return m_elem + i;
//        return end();

//        OK
//        for (size_t i = lo; i < hi; i++)
//            if (m_elem[i] == val)
//                return m_elem + i;
//        return end();
    }

    const_iterator find(const T &val) const { return find(val, 0, m_size); }

    size_t deduplicate() {
        size_t oldSize = m_size, i = 1;
        while (i < m_size)
            find(m_elem[i], 0, i) != end() ? remove(i) : i++;

        return oldSize - m_size;
    }

    // for any 0 <= i < j < m_size, m_elem[i] <= m_elem[j]
    bool disordered() const {
        for (size_t i = 0; i < m_size - 1; i++)
            if (m_elem[i] > m_elem[i + 1])
                return true;
        return false;
    }

    size_t uniquify() {
        size_t i = 0, j = 0;
        while (++j < m_size)
            if (m_elem[i] != m_elem[j])
                m_elem[++i] = std::move(m_elem[j]);
        m_size = ++i;
        return j - i;
    }

    const_iterator search(const T &e) { return search(e, 0, m_size); }

    const_iterator search(const T &e, size_t lo, size_t hi) {
        return binSearch(e, lo, hi);
    }

    inline const_iterator binSearch(const T &e, size_t lo, size_t hi) {
//        lo--;
        while (hi - lo > 1) {
            auto m = (lo + hi) >> 1u;
            e < m_elem[m] ? hi = m : lo = m;
//            e > m_elem[m] ? lo = m : hi = m;
        }
        return m_elem[lo] == e ? begin() + lo : end();
//        return m_elem[hi] == e ? begin() + hi : end();
    }

    const_iterator binSearchSlowTailRec(const T &e, size_t lo, size_t hi) {
        auto m = (lo + hi) >> 1u;
        if (lo == hi)
            return end();
        else if (e == m_elem[m])
            return begin() + m;
        else if (e > m_elem[m])
            binSearchSlowTailRec(e, m + 1, hi);
        else
            binSearchSlowTailRec(e, lo, m);
    }

    inline void sort() { sort(0, m_size); }

    inline void sort(size_t lo, size_t hi) { mergeSort(lo, hi); }

    void bubbleSort(size_t lo, size_t hi) {
        auto sorted = false;

        while (!sorted) {
            sorted = true;

            for (int j = lo; j < hi - 1; j++)
                if (m_elem[j] > m_elem[j + 1]) {
                    sorted = false;
                    swap(j, j + 1);
                }

            hi--;
        }
    }

    inline void mergeSort(size_t lo, size_t hi) {
        T ll[hi - lo], hh[hi - lo];
//        auto ll = new T[hi - lo], hh = new T[hi - lo];
        mergeSort(lo, hi, ll, hh);
    }

    void mergeSort(size_t lo, size_t hi, iterator ll, iterator hh) {
        if (hi - lo <= 1) return;
        auto mi = (lo + hi) >> 1u;
        mergeSort(lo, mi, ll, hh);
        mergeSort(mi, hi, ll, hh);

        if (m_elem[mi - 1] > m_elem[mi])
            merge(lo, mi, hi, ll, hh);
    }

    inline void merge(size_t lo, size_t mi, size_t hi, iterator ll, iterator hh) {
        auto lls = mi - lo, hhs = hi - mi;
        for (size_t i = lo; i < mi; i++)
            ll[i - lo] = std::move_if_noexcept(m_elem[i]);
        for (size_t i = mi; i < hi; i++)
            hh[i - mi] = std::move_if_noexcept(m_elem[i]);

        size_t i = 0, j = 0, k = lo;
        while (i < lls && j < hhs) {
            auto ii = ll[i], jj = hh[j];
            T rr;

            if (ii < jj) {
                rr = ii;
                i++;
            } else {
                rr = jj;
                j++;
            }

            m_elem[k++] = rr;
        }

        for (; i < lls; i++)
            m_elem[k++] = ll[i];
        for (; j < hhs; j++)
            m_elem[k++] = hh[j];
    }

    void show() {
        for (size_t i = 0; i < m_size; i++)
            std::cout << at(i) << " ";
        std::cout << std::endl;
    }
};
