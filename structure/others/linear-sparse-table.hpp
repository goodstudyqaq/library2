#include <bits/stdc++.h>

#include "./sparse-table.hpp"
using namespace std;
/*
基于状压的线性 RMQ 算法
线性算法:
块大小为 w, 在 Word-RAM 模型中 w = Ω(logn), w 位整数
位运算复杂度为 O(1). n n 对于块的结果形成的序列, 使用稀疏表, 由于 w log w ≤ n 这 部分复杂度为 O(n). 对每个块计算块内前缀最小值和后缀最小值, 这部分复杂 度为 O(n).
对每个块在块内计算每个单调栈的二进制表示, 通过位运算 可以使得计算单调栈均摊复杂度和询问复杂的都是 O(1). 复杂度为 O(n) − O(1)

https://www.luogu.com.cn/problem/P3793
https://www.luogu.com.cn/problem/P3865
 */

template <typename T, typename F>
struct LinearSparseTable {
    F f;
    vector<T> V;
    vector<T> newV;
    vector<T> pre_max, suf_max;
    // md_vector<T, 2> pre_max, suf_max;
    map<int, int> two;
    int w;
    vector<int> statues;
    SparseTable<T, F> st;

    LinearSparseTable() = default;

    explicit LinearSparseTable(const vector<T> &v, const F &f, const int _w = 30) : V(v), f(f), w(_w) {
        int n = v.size();
        int block_num = (n + w - 1) / w;
        newV = vector<T>(block_num);
        for (int i = 0; i < block_num; i++) {
            int l = i * w;
            int r = min(i * w + w, n);
            newV[i] = v[l];
            for (int j = l; j < r; j++) {
                newV[i] = f(newV[i], v[j]);
            }
        }

        // 对 newV 做稀疏表
        st = SparseTable<T, F>(newV, f);

        // 对每个块求前缀最大值和后缀最大值
        pre_max = vector<T>(n);
        suf_max = vector<T>(n);
        for (int i = 0; i < n; i++) {
            if (i % w == 0) {
                pre_max[i] = v[i];
            } else {
                pre_max[i] = f(v[i], pre_max[i - 1]);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1 || (i % w) == w - 1) {
                suf_max[i] = v[i];
            } else {
                suf_max[i] = f(v[i], suf_max[i + 1]);
            }
        }

        // 对每个块用单调栈作状压
        statues = vector<int>(n);
        vector<int> stk;
        int status = 0;
        for (int i = 0; i < n; i++) {
            if (i % w == 0) {
                stk.clear();
                status = 0;
            }
            while (stk.size() && v[stk.back()] <= v[i]) {
                status -= (1 << (stk.back() % w));
                stk.pop_back();
            }
            stk.push_back(i);
            status += (1 << (i % w));
            statues[i] = status;
        }
        int now = 1;
        for (int i = 0; i < w; i++) {
            two[now] = i;
            now *= 2;
        }
    }

    inline T fold(int l, int r) const {
        auto lowbit = [&](int x) {
            return x & -x;
        };
        // [l, r)
        r--;
        assert(l <= r);
        int b1 = l / w;
        int b2 = r / w;
        if (b1 == b2) {
            int s = statues[r];
            s = s >> (l % w);
            s = s << (l % w);
            int _low = lowbit(s);
            int idx = two.at(_low);
            return V[idx + b1 * w];
        } else {
            // b1 后缀, b2 前缀
            T res = f(suf_max[l], pre_max[r]);

            if (b1 + 1 <= b2 - 1) {
                res = f(res, st.fold(b1 + 1, b2));
            }
            return res;
        }
    }
};