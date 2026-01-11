#include <bits/stdc++.h>
using namespace std;
/*
树状数组二分:
http://oj.daimayuan.top/course/15/problem/636
https://leetcode.com/problems/finding-mk-average/
*/
//
template <typename T>
struct BIT {
#define lowbit(x) x & -x
    int n;
    vector<T> a;
    int offset;
    // [1, n]
    BIT(int n) : n(n), a(n + 1) { offset = 0; }
    // [l, r] 支持负数
    BIT(int l, int r) {
        // l -> 1
        offset = 1 - l;
        n = r - l + 1;
        a.resize(n + 1);
    }
    BIT() {}

    void add(int x, T v) {
        x += offset;
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    // [1, x]
    T query(int x) {
        x += offset;
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }

    int lower_bound(T x) const {
        // 单调增的时候才能用, 找到第一个下标使得前缀和大于等于 x
        int level = largest_bit(n);
        x += offset;
        int res = 0;
        for (int i = level; i >= 0; i--) {
            if (res + (1 << i) <= n && a[res + (1 << i)] < x) {
                res += (1 << i);
                x -= a[res];
            }
        }
        return res + 1;
    }

    int upper_bound(T x) const {
        // 单调增的时候才能用, 找到第一个下标使得前缀和大于 x
        int level = largest_bit(n);
        x += offset;
        int res = 0;
        for (int i = level; i >= 0; i--) {
            if (res + (1 << i) <= n && a[res + (1 << i)] <= x) {
                res += (1 << i);
                x -= a[res];
            }
        }
        return res + 1;
    }
};

// struct Max {
//     int v;
//     Max(int x = -1E9) : v{x} {}

//     Max &operator+=(Max a) {
//         v = std::max(v, a.v);
//         return *this;
//     }
// };