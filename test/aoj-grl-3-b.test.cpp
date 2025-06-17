// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
#include <bits/stdc++.h>

#include <algorithm>

#include "../graph/others/low-link.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    int n, m;
    cin >> n >> m;
    LowLink<> g(n);
    g.read(m, 0);
    g.build();
    auto &bridge = g.bridge;
    for (auto &v : bridge) {
        tie(v.from, v.to) = minmax({v.from, v.to});
    }
    sort(bridge.begin(), bridge.end(), [&](auto &p, auto &q) {
        return tie(p.from, p.to) < tie(q.from, q.to);
    });
    for (auto &v : bridge) {
        cout << v.from << ' ' << v.to << endl;
    }
    return 0;
}