#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include <bits/stdc++.h>

#include "../graph/connected-components/two-edge-connected-components.hpp"

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
    TwoEdgeConnectedComponents<int> g(n);
    g.read(m, 0);

    g.build();

    auto &group = g.group;
    cout << group.size() << endl;
    for (auto &p : group) {
        cout << p.size();
        for (auto &u : p) {
            cout << ' ' << u;
        }
        cout << endl;
    }
    return 0;
}