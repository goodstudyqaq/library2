#include <bits/stdc++.h>


#include "./point.hpp"
using namespace std;
/*
https://oi-wiki.org/geometry/convex-hull/
https://judge.yosupo.jp/problem/line_add_get_min
*/

namespace geometry {

template <typename T>
T floor_div(T n, T d) {
    return n / d - ((n ^ d) < 0 & n % d != 0);
}

template <typename T>
bool is_right_of_vector(const TPoint<T> &a, const TPoint<T> &b, const TPoint<T> &c, bool boundary_contain) {
    /*
        boundary_contain = true 表示包含边界上的点
    */
    auto cb = b - c;
    auto ba = a - b;
    // cb * ba <= 0 判断 ba 是不是在 cb 的右侧
    // 直接叉积
    T tmp = vmul(cb, ba);
    return tmp < 0 || (!boundary_contain && tmp == 0);
}

template <typename T>
using Polygon = vector<TPoint<T>>;

template <typename T>
pair<Polygon<T>, Polygon<T>> convex_hull_by_andrew(vector<TPoint<T>> &points, bool boundary_contain = false) {
    sort(points.begin(), points.end(), [&](TPoint<T> &a, TPoint<T> &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    vector<int> stk;
    stk.push_back(0);

    int n = points.size();
    vector<int> used(n);
    for (int i = 1; i < n; i++) {
        while (stk.size() >= 2 && is_right_of_vector(points[i], points[stk.back()], points[stk[stk.size() - 2]], boundary_contain)) {
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
            while (stk.size() > tmp && is_right_of_vector(points[i], points[stk.back()], points[stk[stk.size() - 2]], boundary_contain)) {
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
Polygon<T> convex_hull_by_graham(vector<TPoint<T>> &points, bool boundary_contain = false) {
    int n = points.size();
    if (n == 1) {
        return points;
    }
    // 找到 y 最小的，x 最小的点
    sort(points.begin(), points.end());
    auto p0 = points[0];
    for (int i = 0; i < n; i++) {
        points[i] = points[i] - p0;
    }
    // 极角排序
    sort(points.begin(), points.end(), compare_by_polar_angle<T>);

    if (boundary_contain) {
        int sz = n - 1;
        while (sz >= 0 && vmul(points[n - 1] - points[0], points[sz] - points[0]) == 0) sz--;
        for (int l = sz + 1, r = n - 1; l < r; l++, r--) {
            swap(points[l], points[r]);
        }
    }
    vector<int> stk(n);
    int k = 0;
    stk[k++] = 0;
    for (int i = 1; i < n; i++) {
        while (k >= 2 && is_right_of_vector(points[i], points[stk[k - 1]], points[stk[k - 2]], boundary_contain)) {
            k--;
        }
        stk[k++] = i;
    }
    Polygon<T> convex;
    for (int i = 0; i < k; i++) {
        convex.push_back(points[stk[i]] + p0);
    }
    return convex;
}

template <typename T>
T getMinDotProduct(const Polygon<T> convex, const TPoint<T> &p) {
    /*
    求凸包 convex 上的点的向量 x 与向量 p 的点积的最小值, 点积的几何意义是 x 在 p 上的投影的积，方向相同为正，方向不同为负.
    可以发现当 p.y 是正的，那么最小值一定出现在凸包的下半部分。如果 p.y 是负的，那么最小值出现在凸包的上半部分.(感觉很正确)
    */
    if (p.y < 0) {
        // 翻转
    }
}

}  // namespace geometry
