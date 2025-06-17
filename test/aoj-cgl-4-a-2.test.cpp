// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
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

    auto convex = geometry::convex_hull_by_graham(points, true);
    debug(convex);
    int sz = convex.size();
    cout << sz << endl;

    for (int i = 0; i < sz; i++) {
        cout << convex[i].x << ' ' << convex[i].y << endl;
    }
    return 0;
}
