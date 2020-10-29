//
// Created by Ray Eldath on 2020/10/23.
//

#ifndef ALGORITHM_5_H
#define ALGORITHM_5_H

#endif //ALGORITHM_5_H

#include <functional>
#include <algorithm>
#include <stack>
#include <queue>
#include <iostream>

template<typename T>
class BinTree;

template<typename T>
struct BinNode {
    using iterator = BinNode<T> *;

    T data;
    iterator parent, left, right;
    int height;

    explicit BinNode() : parent(nullptr), left(nullptr), right(nullptr), height(0) {}

    explicit BinNode(T e, iterator p = nullptr, iterator l = nullptr, iterator r = nullptr, int h = 0) :
            data(e), parent(p), left(l), right(r), height(h) {}

    iterator insert_left(const T &e) { return left = new BinNode(e, this); }

    iterator insert_right(const T &e) { return right = new BinNode(e, this); }

//    void traverse(std::function<void(T)> func) {
//
//    }

    iterator succ() {
        using Tree = BinTree<T>;
        iterator s = this;
        if (right != nullptr) {
            s = right;
            while (Tree::has_left(s)) s = s->left;
        } else {
            while (Tree::is_right(s)) s = s->parent; // 如果当前节点是右孩子，上行；直到当前节点为祖先节点的第一个左孩子
            s = s->parent; // 在这个左孩子上上行一步，即得祖先节点
        }
        return s;
    }
};

template<typename T>
class BinTree {
private:
    friend BinNode<T>;

    using iterator = typename BinNode<T>::iterator;
    using tree_iterator = BinTree<T> *;
    using Visitor = std::function<void(T)>;

    iterator m_root;
    size_t m_size;

    static inline bool is_root(iterator x) { return !(x->parent); }

    static inline bool is_left(iterator x) { return is_root(x) == false && x->parent->left == x; }

    static inline bool has_left(iterator x) { return x->left != nullptr; }

    static inline bool has_right(iterator x) { return x->right != nullptr; }

    static inline bool is_right(iterator x) { return is_root(x) == false && x->parent->right == x; }

    inline iterator &from_parent_to(iterator x) {
        if (is_root(x))
            return m_root;
        else
            return is_left(x) ? x->parent->left : x->parent->right;
    }

    inline int stature(iterator x) { return x ? x->height : -1; }

    inline int update_height(iterator x) { return x->height = std::max(stature(x->left), stature(x->right)) + 1; }

    void update_height_and_above(iterator x) {
        while (x) {
            if (stature(x) == update_height(x))
                return;
            x = x->parent;
        }
    }

    size_t remove_at(iterator x) {
        if (x == nullptr) return 0;
        int n = 1 + remove_at(x->left) + remove_at(x->right);
        release(x);
        return n;
    }

    template<typename TT>
    static inline void release(TT *&p) {
        if (std::is_array<TT>())
            delete[] p;
        else delete p;
    }

    inline void cal_undermost(iterator e, std::stack<iterator> &s) {
        s.push(e);
        while (e != nullptr) {
            if (has_left(e))
                s.push(e = e->left);
            else
                s.push(e = e->right);
        }
        s.pop();
    }

public:

    BinTree() : m_size(0), m_root(nullptr) {}

    ~BinTree() {
        if (m_size > 0)
            remove(m_root);
    }

    inline iterator root() const { return m_root; }

    inline size_t size() const { return m_size; }

    inline bool empty() const { return !m_root; }

    template<typename ...Args>
    iterator emplace_root(Args &&... args) { return m_root = new BinNode<T>(*(new T(std::forward<Args>(args)...))); }

    template<typename ...Args>
    iterator emplace_right(iterator x, Args &&... args) {
        m_size++;
        x->insert_right(*(new T(std::forward<Args>(args)...)));
        update_height_and_above(x);
        return x->right;
    }

    template<typename ...Args>
    iterator emplace_left(iterator x, Args &&... args) {
        m_size++;
        x->insert_left(*(new T(std::forward<Args>(args)...)));
        update_height_and_above(x);
        return x->left;
    }

    iterator attach_left(iterator x, tree_iterator &S) {
        if ((x->left = S->m_root) != nullptr)
            S->m_root->parent = x;
        m_size += S->m_size;
        update_height_and_above(x);
        S->m_root = nullptr;
        S->m_size = 0;
        release(S);
        S = nullptr;
        return x;
    }

    iterator attach_right(iterator x, tree_iterator &S) {
        if ((x->right = S->m_root) != nullptr)
            S->m_root->parent = x;
        m_size += S->m_size;
        update_height_and_above(x);
        S->m_root = nullptr;
        S->m_size = 0;
        release(S);
        S = nullptr;
        return x;
    }

    size_t remove(iterator x) {
        from_parent_to(x) = nullptr;
        update_height_and_above(x->parent);
        int n = remove_at(x);
        m_size -= n;
        return n;
    }

    tree_iterator secede(iterator x) {
        from_parent_to(x) = nullptr;
        update_height_and_above(x->parent);
        auto S = new BinTree<T>();
        S->m_root = x;
        x->parent = nullptr;
        m_size -= S->size();
        return S;
    }

    void traverse_preorder_iterate(iterator x, Visitor visitor) {
//        if (x == nullptr) return;
//        visitor(x->data);
//        std::cout << x->data << ": " << has_left(x) << " " << has_right(x) << std::endl;
//        traverse_preorder_iterate(x->left, visitor);
//        traverse_preorder_iterate(x->right, visitor);

        std::stack<iterator> nodes;
        while (true) {
            while (x != nullptr) {
                visitor(x->data);
                nodes.push(x);
                x = x->left;
            }
            if (nodes.empty()) break;
            x = nodes.top();
            nodes.pop();
            x = x->right;
        }
    }

    void traverse_inorder_iterate(iterator x, Visitor visitor) {
        std::stack<iterator> nodes;
        while (true) {
            while (x != nullptr) {
                nodes.push(x);
                x = x->left;
            }
            if (nodes.empty()) break;
            x = nodes.top();
            nodes.pop();
            visitor(x->data);
            x = x->right;
        }
//        注意到先序和中序遍历的迭代版仅有 visitor(x->data) 位置的差别：
//        前者是在沿最左侧通路下行时一并访问，后者是下行完成后访问栈顶。
//        这样的一致性是基于以下事实：先序和中序遍历的递归版，在访问当前节点的
//        左孩子或右孩子时，总有一次是尾递归的。
//        考虑到后序遍历没有这样的性质，其迭代解必然是完全不同的结构。
    }

    void traverse_inorder_iterate_compact(iterator x, Visitor visitor) {
        bool backtracked = false; // 省去栈，空间效率更高
//        回溯标记：当上行时置真。
//        本法关键在于理解当上行时说明当前节点的左子树已经遍历过了，只需处理右子树
//        但同时要注意到：succ() 方法依赖于 parent 指针的存在，这事实上增加了
//        整体的空间消耗。

        while (true) {
            if (!backtracked && has_left(x))
                x = x->left;
            else {
                visitor(x->data);

                if (has_right(x)) {
                    x = x->right;
                    backtracked = false;
                } else {
                    if ((x = x->succ()) == nullptr) break;
                    backtracked = true;
                }
            }
        }
    }

    void traverse_inorder_recursive(iterator x, Visitor visitor) {
        if (x == nullptr) return;
        traverse_inorder_recursive(x->left, visitor);
        visitor(x->data);
        traverse_inorder_recursive(x->right, visitor);
    }

    void traverse_postorder_iterate(iterator x, Visitor visitor) {
        std::stack<iterator> nodes;
        if (x != nullptr) cal_undermost(x, nodes);

        while (!nodes.empty()) {
            x = nodes.top();
            nodes.pop();
            visitor(x->data);

            if (is_left(x) && has_right(x->parent)) // 如果有右兄弟
                cal_undermost(x->parent->right, nodes); // 入栈右兄弟下行至最底端的路径
        }
    }

    void traverse_levelorder(iterator x, Visitor visitor) {
        std::queue<iterator> nodes;
        if (x != nullptr) nodes.push(x);

        while (!nodes.empty()) {
            x = nodes.front();
            nodes.pop();
            visitor(x->data);

            if (has_left(x)) nodes.push(x->left);
            if (has_right(x)) nodes.push(x->right);
        }
    }
};