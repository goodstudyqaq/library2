#pragma once

#include <bits/stdc++.h>

#include <functional>
using namespace std;
// https://codeforces.com/contest/2126/problem/G2
struct Info {
    // 默认值
    Info() {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info();
    }
    string to_string() {
        return "";
    }
};
// 能开多大就开多大
// 线段树 -> 4 * N. 每次操作就要增加 log(N) 个点，要操作 N 次那么总共要的就是 :4N + Nlog(N).
// N = 2e5 4N + Nlog(N) = 8e5 + 34e5 = 42e5
const int maxn = 64e5;
int left_son[maxn], right_son[maxn];
int cnt = 0;

Info info[maxn];

struct PersistentSegmentTree {
#define lson l, m, left_son[rt]
#define rson m + 1, r, right_son[rt]
    PersistentSegmentTree(int n) : n(n), merge(Info::merge) {}
    int build(vector<Info>& init) {
        function<int(int, int)> build = [&](int l, int r) -> int {
            if (l == r) {
                int p = new_node();
                info[p] = init[l];
                return p;
            }
            int m = l + r >> 1;
            int p = new_node();
            left_son[p] = build(l, m);
            right_son[p] = build(m + 1, r);
            push_up(p, l, r);
            return p;
        };
        return build(0, n - 1);
    }
    int update(int L, const Info& v, int rt) {
        return update(L, v, 0, n - 1, rt);
    }

    int assign(int L, const Info& v, int rt) {
        return assign(L, v, 0, n - 1, rt);
    }

    Info rangeQuery(int L, int R, int rt) {
        return rangeQuery(L, R - 1, 0, n - 1, rt);
    }

   private:
    int n;
    const function<Info(const Info&, const Info&, int, int)> merge;

    int new_node() {
        left_son[cnt] = -1;
        right_son[cnt] = -1;
        info[cnt] = Info();
        return cnt++;
    }

    void push_up(int rt, int l, int r) {
        info[rt] = merge(info[left_son[rt]], info[right_son[rt]], l, r);
    }

    int update(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            int p = new_node();
            info[p] = merge(info[rt], v, l, r);
            return p;
        }
        int m = l + r >> 1;
        int p = new_node();
        if (L <= m) {
            left_son[p] = update(L, v, lson);
            right_son[p] = right_son[rt];
        } else {
            right_son[p] = update(L, v, rson);
            left_son[p] = left_son[rt];
        }
        push_up(p, l, r);
        return p;
    }

    int assign(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            int p = new_node();
            info[p] = v;
            return p;
        }
        int m = l + r >> 1;
        int p = new_node();
        if (L <= m) {
            left_son[p] = assign(L, v, lson);
            right_son[p] = right_son[rt];
        } else {
            right_son[p] = assign(L, v, rson);
            left_son[p] = left_son[rt];
        }
        push_up(p, l, r);
        return p;
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson), l, r);
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }
};