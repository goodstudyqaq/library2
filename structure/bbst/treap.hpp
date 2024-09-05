#include "../../utils/utils.hpp"

template <typename T>
struct Node {
    int ch[2];
    T val, tag;
    int rk;
    int size = 0;  // 以当前节点为根子树的大小

    Node() {
        ch[0] = ch[1] = 0;
        val = 0;
    }
    Node(T val) : val(val) {
        tag = T();
        size = 1;
        rk = mrand();
        ch[0] = ch[1] = 0;
    }
};

template <typename T>
struct NonRotatingTreap {
    NonRotatingTreap() {
        nodes.clear();
        nodes.push_back(Node<T>());
        root = 0;
    }

    int root;
    vector<Node<T>> nodes;

    inline void push_up(int u) {
        nodes[u].size = nodes[nodes[u].ch[0]].size + 1 + nodes[nodes[u].ch[1]].size;
    }

    inline void push_tag(int x, T v) {
        if (x) {
            nodes[x].val += v;
            nodes[x].tag += v;
        }
    }

    void push_down(int u) {
        if (nodes[u].tag == T()) {
            return;
        }
        push_tag(nodes[u].ch[0], nodes[u].tag);
        push_tag(nodes[u].ch[1], nodes[u].tag);
        nodes[u].tag = T();
    }

    int new_node(T val) {
        int u = nodes.size();
        nodes.push_back(Node(val));
        return u;
    }

    void split_by_value(int u, T k, int &x, int &y) {
        if (!u) {
            x = y = 0;
            return;
        }
        push_down(u);
        if (nodes[u].val <= k) {
            x = u;
            split_by_value(nodes[u].ch[1], k, nodes[x].ch[1], y);
        } else {
            y = u;
            split_by_value(nodes[u].ch[0], k, x, nodes[y].ch[0]);
        }
        push_up(u);
    }

    void split_by_rank(int u, int rank, int &x, int &y) {
        if (!u) {
            x = 0, y = 0;
            return;
        }
        push_down(u);
        if (nodes[nodes[u].ch[0]].size + 1 <= rank) {
            x = u;
            split_by_rank(nodes[u].ch[1], rank - nodes[nodes[u].ch[0]].size - 1, nodes[x].ch[1], y);
        } else {
            y = u;
            split_by_rank(nodes[u].ch[0], rank, x, nodes[y].ch[0]);
        }
        push_up(u);
    }

    int merge(int x, int y) {
        if (!x || !y) {
            return x + y;
        }
        push_down(x);
        push_down(y);
        if (nodes[x].rk < nodes[y].rk) {
            nodes[x].ch[1] = merge(nodes[x].ch[1], y);
            push_up(x);
            return x;
        } else {
            nodes[y].ch[0] = merge(x, nodes[y].ch[0]);
            push_up(y);
            return y;
        }
    }

    inline void insert(T val) {
        int x, y;
        split_by_value(root, val, x, y);
        root = merge(merge(x, new_node(val)), y);
    }

    T qmin(int x) {
        while (nodes[x].ch[0]) {
            push_down(x);
            x = nodes[x].ch[0];
        }
        return nodes[x].val;
    }

    T qmax(int x) {
        while (nodes[x].ch[1]) {
            push_down(x);
            x = nodes[x].ch[1];
        }
        return nodes[x].val;
    }
};