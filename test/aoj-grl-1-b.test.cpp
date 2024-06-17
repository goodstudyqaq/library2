#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B"

#include <bits/stdc++.h>

#include <limits>

#include "../graph/shortest-path/bellman-ford.hpp"

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
    int n, m, s;
    cin >> n >> m >> s;
    Edges<> es;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        es.emplace_back(u, v, w);
    }

    auto dist = bellman_ford(es, n, s);
    for (auto& d : dist) {
        if (d == numeric_limits<int>::min()) {
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }

    for (auto& d : dist) {
        if (d == numeric_limits<int>::max()) {
            cout << "INF" << endl;
        } else {
            cout << d << endl;
        }
    }
}