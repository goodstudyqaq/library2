#include <bits/stdc++.h>

#include <type_traits>

#include "./base.hpp"
#include "./point.hpp"
using namespace std;
/*
todo: https://noshi91.hatenablog.com/entry/2021/03/23/200810
https://github.com/ei1333/library/blob/master/structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
*/

namespace geometry {
template <typename T>
struct ConvexHullTrick {
    ConvexHullTrick() = default;
    ConvexHullTrick(const vector<TPoint<T>> &_points, bool is_min = true) : points(_points), is_min(is_min) {
        int n = points.size();
        if (!is_min) {
            for (int i = 0; i < n; i++) {
                points[i].x *= -1;
                points[i].y *= -1;
            }
        }
        // 和 Andrew 算法类似
        sort(points.begin(), points.end(), [&](TPoint<T> &a, TPoint<T> &b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        });

        // 只求下凸包
        vector<int> stk;
        stk.push_back(0);
        for (int i = 1; i < n; i++) {
            while (stk.size() >= 2 && check(points[i], points[stk.back()], points[stk[stk.size() - 2]])) {
                stk.pop_back();
            }
            stk.push_back(i);
        }

        for (auto it : stk) {
            convex.emplace_back(points[it]);
        }

        reverse(convex.begin(), convex.end());
    }
    T query(T x) {
        assert(!convex.empty());
        int l = 0, r = convex.size() - 2;
        T res = min(get_y(0, x), get_y(convex.size() - 1, x));

        while (l <= r) {
            int m = l + r >> 1;
            T tmp1 = get_y(m, x);
            T tmp2 = get_y(m + 1, x);
            if (tmp1 > tmp2) {
                res = min(res, tmp2);
                l = m + 1;
            } else {
                res = min(res, tmp1);
                r = m - 1;
            }
        }
        if (!is_min) res *= -1;
        return res;
    }

   private:
    bool is_min;
    vector<TPoint<T>> convex, points;

    T floor_div(T a, T b) {
        assert(b != 0);
        return a / b - ((a ^ b) < 0 & (a % b != 0));
    }

    bool check(const TPoint<T> &a, const TPoint<T> &b, const TPoint<T> &c) {
        // a.x > b.x > c.x
        // return (b.x-a.x)*(c.y-b.y) >= (b.y-a.y)*(c.x-b.x); -> (a.x-b.x)*(c.y-b.y) <= (b.y-a.y)*(b.x-c.x)
        if (a.x == b.x || b.x == c.x) {
        // if (b.y == a.y || b.y == c.y) {
            return sign(b.x - a.x) * sign(c.y - b.y) >= sign(b.y - a.y) * sign(c.x - b.x);
        }
        if constexpr (is_integral<T>::value) {
            return floor_div(b.y - a.y, a.x - b.x) >= floor_div(c.y - b.y, b.x - c.x);
        }
        return (b.x - a.x) * sign(c.y - b.y) / abs(b.y - a.y) >= (c.x - b.x) * sign(b.y - a.y) / (c.y - b.y);
    }

    T get_y(int idx, T x) {
        return convex[idx].x * x + convex[idx].y;
    }
};

}  // namespace geometry
