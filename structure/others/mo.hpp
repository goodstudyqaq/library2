#pragma once
#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/contest/220/submission/359114778
// 复杂度: O(n ^ {3 / 2})
struct Mo {
    struct Query {
        int l, r, idx;
        int block;
    };

    int n = 0;
    int len = 1;
    vector<Query> qs;

    Mo(int n_ = 0) { init(n_); }

    void init(int n_) {
        n = n_;
        len = 1;
        qs.clear();
    }

    // 手动设置块长（可选）
    void set_block_len(int blen) {
        len = max(1, blen);
        for (auto &q : qs) q.block = q.l / len;
    }

    // 添加一个左闭右闭查询 [l, r]，返回 query id
    int add_query(int l, int r) {
        int id = (int)qs.size();
        Query q{l, r, id, 0};
        q.block = (len > 0 ? l / len : 0);
        qs.push_back(q);
        return id;
    }

    static bool cmp(const Query& a, const Query& b) {
        if (a.block != b.block) return a.block < b.block;
        if (a.r == b.r) return false;
        // 奇偶块优化：奇数块 r 反向
        return (a.block & 1) ? (a.r > b.r) : (a.r < b.r);
    }

    // add(idx), del(idx), on_query(qid) 都是可调用对象（lambda / function / functor）
    template <class Add, class Del, class OnQuery>
    void run(Add add, Del del, OnQuery on_query) {
        if (qs.empty()) return;

        // 如果用户没手动设置，就自动挑一个块长
        if (len <= 1 && n > 1) {
            int q = (int)qs.size();
            len = max(1, (int)(n / max(1.0, sqrt((double)q))));
        }
        for (auto &qq : qs) qq.block = qq.l / len;

        sort(qs.begin(), qs.end(), cmp);

        int L = 0, R = -1; // 当前区间 [L, R]

        for (auto &qu : qs) {
            while (L > qu.l) { --L; add(L); }
            while (R < qu.r) { ++R; add(R); }
            while (L < qu.l) { del(L); ++L; }
            while (R > qu.r) { del(R); --R; }

            on_query(qu.idx);
        }
    }
};