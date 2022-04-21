//
// Created by ray-eldath on 22-4-22.
//
#include <queue>

using namespace std;

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right) : val(_val), left(_left), right(_right), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

Node *connect(Node *root) {
    if (!root) return root;
    queue<Node *> q;
    q.emplace(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            Node *f = q.front();
            q.pop();
            if (i < n - 1) f->next = q.front();
            if (f->left) q.emplace(f->left);
            if (f->right) q.emplace(f->right);
        }
    }
    return root;
}

Node *connect2(Node *root) {
    if (!(root && root->left && root->right)) return root;
    root->left->next = root->right;
    if (root->next) root->right->next = root->next->left;
    connect2(root->left);
    connect2(root->right);
    return root;
}

int main() {
    connect2(new Node(1, new Node(2, new Node(4), new Node(5)), new Node(3, new Node(6), new Node(7))));
    connect2(nullptr);
}