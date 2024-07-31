#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include <bits/stdc++.h>

#include "../geometry/convex-hull.hpp"
#include "../structure/others/binary-grouping.hpp"

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
using Data = geometry::TPoint<long long>;

struct Structure {
    vector<Data> datas;
    vector<Data> convexHull;
    virtual void add(const Data &d) {
        datas.emplace_back(d);
    }

    void build() {
        convexHull = geometry::convexHullByAndrew(datas).first;
    }
    static Structure merge(const Structure &s1, const Structure &s2) {
        Structure new_s;
        for (auto &d : s1.datas) {
            new_s.add(d);
        }
        for (auto &d : s2.datas) {
            new_s.add(d);
        }
        new_s.build();
        return new_s;
    }

    long long query(long long x) {
        // if (convexHull.size() == 1) {
        //     return convexHull[0].first * x + convexHull[0].second;
        // }
        debug(convexHull);
        long long res = numeric_limits<long long>::max() / 2;
        res = min(convexHull[0].x * x + convexHull[0].y, convexHull.back().x * x + convexHull.back().y);
        int l = 0, r = convexHull.size() - 2;
        while (l <= r) {
            int m = l + r >> 1;
            long long tmp1 = convexHull[m].x * x + convexHull[m].y;
            long long tmp2 = convexHull[m + 1].x * x + convexHull[m + 1].y;
            if (tmp1 > tmp2) {
                res = min(res, tmp2);
                l = m + 1;
            } else {
                res = min(res, tmp1);
                r = m - 1;
            }
        }
        return res;
    }

    size_t size() const { return datas.size(); }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    BinaryGrouping<Structure, Data> bg;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        bg.insert({a, b});
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            long long a, b;
            cin >> a >> b;
            bg.insert({a, b});
        } else {
            long long p;
            cin >> p;
            auto &structures = bg.structures;
            long long res = numeric_limits<long long>::max() / 2;
            for (auto &s : structures) {
                res = min(res, s.query(p));
            }
            cout << res << endl;
        }
    }
    return 0;
}