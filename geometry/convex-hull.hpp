#include <bits/stdc++.h>

#include "./point.hpp"
using namespace std;
/*
https://oi-wiki.org/geometry/convex-hull/
https://judge.yosupo.jp/problem/line_add_get_min
*/

namespace geometry {

template <typename T>
using Polygon = vector<TPoint<T>>;

template <typename T>
pair<Polygon<T>, Polygon<T>> convexHullByAndrew(vector<TPoint<T>> &points, bool boundaryContain = false) {
    sort(points.begin(), points.end(), [&](TPoint<T> &a, TPoint<T> &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    vector<int> stk;
    stk.push_back(0);

    int n = points.size();
    vector<int> used(n);
    for (int i = 1; i < n; i++) {
        while (stk.size() >= 2 && check(points[i], points[stk.back()], points[stk[stk.size() - 2]], boundaryContain)) {
            used[stk.back()] = 0;
            stk.pop_back();
        }
        used[i] = 1;
        stk.push_back(i);
    }
    Polygon<T> lower_convex_hull, upper_convex_hull;
    int tmp = stk.size();  // 下凸包的大小

    for (int i = n - 1; i >= 0; i--) {
        if (!used[i]) {
            while (stk.size() > tmp && check(points[i], points[stk.back()], points[stk[stk.size() - 2]], boundaryContain)) {
                used[stk.back()] = 0;
                stk.pop_back();
            }
            used[i] = 1;
            stk.push_back(i);
        }
    }

    for (int i = 0; i < tmp; i++) {
        lower_convex_hull.emplace_back(points[stk[i]]);
    }
    for (int i = tmp - 1; i < stk.size(); i++) {
        upper_convex_hull.emplace_back(points[stk[i]]);
    }
    return {lower_convex_hull, upper_convex_hull};
}

template <typename T>
vector<TPoint<T>> convexHullByGraham(vector<TPoint<T>> &points) {
}

template <typename T>
T getMinDotProduct(const Polygon<T> convex, const Point &p) {
    /*
    求凸包 convex 上的点的向量 x 与向量 p 的点积的最小值, 点积的几何意义是 x 在 p 上的投影的积，方向相同为正，方向不同为负.
    可以发现当 p.y 是正的，那么最小值一定出现在凸包的下半部分。如果 p.y 是负的，那么最小值出现在凸包的上半部分.(感觉很正确)
    */
    if (p.y < 0) {
        // 翻转
    }
}

}  // namespace geometry
