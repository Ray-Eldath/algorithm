//
// Created by Ray Eldath on 2020/10/16.
//

#ifndef ALGORITHM_3_H
#define ALGORITHM_3_H

#endif //ALGORITHM_3_H

#include <iostream>

template<typename T>
struct ListNode {
    using iterator = ListNode<T> *;
    using const_iterator = const ListNode<T> *;

    T data;
    iterator pred = nullptr, succ = nullptr;

    explicit ListNode() : ListNode(0) {};

    explicit ListNode(T e, iterator p = nullptr, iterator s = nullptr)
            : data(e), pred(p), succ(s) {};

    inline T &operator*() { return data; }

//    TODO: fix foreach
//    inline const_iterator operator++() {
//        cout << "called" << endl;
//        return this;
//    }
//
//    inline const_iterator operator++(int) {
//        cout << "called" << endl;
//        return this;
//    }

    iterator insert_pred(const T &e) {
        auto x = new ListNode(e, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }

    iterator insert_succ(const T &e) {
        auto x = new ListNode(e, this, succ);
        succ->pred = x;
        succ = x;
        return x;
    }
};

template<typename T>
class List {
private:
    using iterator = typename ListNode<T>::iterator;
    using const_iterator = typename ListNode<T>::const_iterator;

    size_t m_size;
    iterator m_header, m_trailer;

    size_t clear() {
        auto oldSize = m_size;
        while (m_size > 0)
            remove(m_header->succ);
        return oldSize;
    }

public:
    explicit List() {
        m_header = new ListNode<T>;
        m_trailer = new ListNode<T>;
        m_header->succ = m_trailer;
        m_trailer->pred = m_header;
        m_size = 0;
    }

    List(const std::initializer_list<T> &elem) : List() {
        for (auto &&e:elem)
            push_back(e);
    }

    ~List() {
        clear();
        delete m_header;
        delete m_trailer;
    }

    size_t size() const { return m_size; }

    bool empty() const { return m_size <= 0; }

    inline iterator header() const { return m_header; }

    inline iterator trailer() const { return m_trailer; }

    inline iterator begin() const { return m_header->succ; }

    inline iterator end() const { return m_trailer; }

    bool valid(iterator p) const { return p && p != m_header && p != m_trailer; }

    iterator find(const T &e, size_t n, iterator p) const {
        while (n-- > 0) {
            if (e == p->data)
                return p;
            p = p->pred;
        }
        return begin();
    }

    const_iterator push_front(const T &e) {
        m_size++;
        return m_header->insert_succ(e);
    }

    const_iterator push_back(const T &e) {
        m_size++;
        return m_trailer->insert_pred(e);
    }

    iterator insert_after(iterator p, const T &e) {
        m_size++;
        return p->insert_succ(e);
    }

    iterator insert_before(iterator p, const T &e) {
        m_size++;
        return p->insert_pred(e);
    }

    T remove(iterator p) {
        T e = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p;
        m_size--;
        return e;
    }

    // deduplicate(), uniquify() omitted.

    void show() {
        for (auto x = begin(); x != end(); x = x->succ)
            std::cout << x->data << " ";
        std::cout << std::endl;
    }

    iterator search(const T &e, size_t n, iterator p) const {
        while (n-- >= 0)
            if ((p = p->pred)->data <= e)
                break;
        return p;
    }

    inline void sort() { sort(begin(), m_size); }

    inline void sort(iterator lo, size_t n) { mergeSort(lo, n); /* TODO */ }

    void insertionSort(iterator lo, size_t n) {
        while (n--) {
            search(lo->data, n, lo)->insert_succ(lo->data);
            remove(lo);
            lo = lo->succ;
        }
    }

    void selectionSort(iterator lo, size_t n) {
        iterator hi = lo;
        for (size_t i = 0; i < n; i++) hi = hi->succ;

        while (lo != hi) {
            auto max = lo;
            for (auto x = lo; x != hi; x = x->succ)
                if (x->data > max->data)
                    max = x;

            swap(hi->pred, max);
//            insert_before(hi, max->data);
//            remove(max);
            hi = hi->pred;
        }
    }

    inline void swap(iterator a, iterator b) {
        auto t = a->data;
        a->data = b->data;
        b->data = t;
    }

    void mergeSort(iterator p, size_t n) {
        if (n < 2) return;
        auto m = n >> 1u;
        auto q = p;
        for (size_t i = 0; i < m; i++) q = q->succ;

        mergeSort(p, m);
        mergeSort(q, n - m);

        merge(p, m, *this, q, n - m);
    }

    void merge(iterator p, size_t n, List<int> &source, iterator q, size_t m) {
        while (m > 0 && p != q) {
            if (n > 0 && p->data <= q->data) {
                p = p->succ;
                n--;
            } else {
                insert_before(p, source.remove((q = q->succ)->pred));
                m--;
            }
        }

//        while (m > 0 && n > 0) {
//            if (q->data < p->data) {
//                auto pNext = p->succ;
//                auto qNext = q->succ;
//                auto qPred = q->pred;
//
//                if (p->succ == q) {
//                    swap(p, q);
//                    p = p->succ;
//                    q = q->succ;
//                } else {
//                    p->succ = q;
//                    q->pred = p;
//                    q->succ = pNext;
//                    pNext->pred = q;
//                    swap(p, q);
//                    q = qNext;
//                    qPred->succ = q;
//                    q->pred = qPred;
//                    p = p->succ;
//                }
//                m--;
//            } else {
//                p = p->succ;
//                n--;
//            }
//        }
    }
};