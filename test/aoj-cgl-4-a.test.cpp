#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"
#include <bits/stdc++.h>

#include "../geometry/convex-hull.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    using Point = geometry::TPoint<int>;

    vector<Point> points;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    auto convex = geometry::convexHullByAndrew(points, true);
    debug(convex);
    int sz = convex.first.size() + convex.second.size() - 2;
    cout << sz << endl;

    int begin = 0;

    while (begin + 1 < convex.first.size() && convex.first[begin + 1].y < convex.first[begin].y) {
        begin++;
    }

    for (int i = begin; i < convex.first.size(); i++) {
        cout << convex.first[i].x << ' ' << convex.first[i].y << endl;
    }
    for (int i = 1; i < convex.second.size() - 1; i++) {
        cout << convex.second[i].x << ' ' << convex.second[i].y << endl;
    }
    for (int i = 0; i < begin; i++) {
        cout << convex.first[i].x << ' ' << convex.first[i].y << endl;
    }
    return 0;
}