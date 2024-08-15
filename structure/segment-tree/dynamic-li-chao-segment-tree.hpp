#include <bits/stdc++.h>
using namespace std;
template <typename T, T x_low, T x_high, T _default>
struct DynamicLiChaoSegmentTree {
    struct Line {
        T a, b;
        Line(T a, T b) : a(a), b(b) {}
        inline T get(const T& x) const { return a * x + b; }
    };

    struct Node {
        Line x;
        Node *l, *r;
        Node(const Line &x) : x{x}, l{nullptr}, r{nullptr} {}
    };
    Node *root;
    DynamicLiChaoSegmentTree() : root(nullptr) {}

    Node *add_line(Line &x, const T &l, const T &r, Node *rt) {
        if (!rt) {
            return new Node(x);
        }
        T rt_l = rt->x.get(l), rt_r = rt->x.get(r);
        T x_l = x.get(l), x_r = x.get(r);

        if (rt_l <= x_l && rt_r <= x_r) {
            return rt;
        } else if (x_l <= rt_l && x_r <= rt_r) {
            rt->x = x;
            return rt;
        } else {
            T m = l + r >> 1;
            T rt_m = rt->x.get(m), x_m = x.get(m);
            if (rt_m > x_m) {
                swap(rt->x, x);
            }
            // rt->x 现在在 m 最优

            if (x.get(l) < rt->x.get(l)) {
                rt->l = add_line(x, l, m, rt->l);
            } else {
                rt->r = add_line(x, m + 1, r, rt->r);
            }
            return rt;
        }
    }

    void add_line(const T &a, const T &b) {
        Line x(a, b);
        root = add_line(x, x_low, x_high, root);
    }

    Node *add_segment(Line &x, const T &L, const T &R, const T &l, const T &r, Node *rt) {
        if (L <= l && r <= R) {
            Line y{x};
            return add_line(y, l, r, rt);
        }
        if (rt) {
            T rt_l = rt->x.get(l), rt_r = rt->x.get(r);
            T x_l = x.get(l), x_r = x.get(r);
            if (rt_l <= x_l && rt_r <= x_r) return rt;
        } else {
            rt = new Node(Line(0, _default));
        }
        T m = l + r >> 1;
        if (L <= m) {
            rt->l = add_segment(x, L, R, l, m, rt->l);
        }
        if (R > m) {
            rt->r = add_segment(x, L, R, m + 1, r, rt->r);
        }
        return rt;
    }

    void add_segment(const T &l, const T &r, const T &a, const T &b) {
        Line x(a, b);
        root = add_segment(x, l, r - 1, x_low, x_high, root);
    }

    T query(const T &L, const T &l, const T &r, const Node *rt) {
        if (!rt) {
            return _default;
        }
        if (l == r) {
            return rt->x.get(L);
        }
        T m = l + r >> 1;
        if (L <= m) {
            return min(rt->x.get(L), query(L, l, m, rt->l));
        } else {
            return min(rt->x.get(L), query(L, m + 1, r, rt->r));
        }
    }
    T query(const T &x) {
        return query(x, x_low, x_high, root);
    }
};