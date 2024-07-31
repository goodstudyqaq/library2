#include <bits/stdc++.h>

#include "./point.hpp"
using namespace std;
/*
https://oi-wiki.org/geometry/convex-hull/
*/

namespace geometry {
template <typename T>
pair<vector<TPoint<T>>, vector<TPoint<T>>> convexHullByAndrew(vector<TPoint<T>> &points) {
    sort(points.begin(), points.end(), [&](TPoint<T> &a, TPoint<T> &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    vector<int> stk;
    stk.push_back(0);

    int n = points.size();
    vector<int> used(n);
    for (int i = 1; i < n; i++) {
        while (stk.size() >= 2 && check(points[i], points[stk.back()], points[stk[stk.size() - 2]])) {
            used[stk.back()] = 0;
            stk.pop_back();
        }
        used[i] = 1;
        stk.push_back(i);
    }
    vector<TPoint<T>> lower_convex_hull, upper_convex_hull;
    int tmp = stk.size();  // 下凸包的大小

    for (int i = n - 1; i >= 0; i--) {
        if (!used[i]) {
            while (stk.size() > tmp && check(points[i], points[stk.back()], points[stk[stk.size() - 2]])) {
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

// template <typename T>
// vector<TPoint<T>> convexHullByGraham(vector<TPoint<T>> &points) {

// }

}  // namespace geometry
