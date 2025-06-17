// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_edge_connected_components
#include <bits/stdc++.h>

#include "../graph/connected-components/incremental-bridge-connectivity.hpp"

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
    IncrementalBridgeConnectivity ibc(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ibc.add_edge(u, v);
    }
    vector<vector<int>> groups(n);
    for (int i = 0; i < n; i++) {
        groups[ibc.find(i)].push_back(i);
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        if ((int)groups[i].size()) k++;
    }

    cout << k << endl;
    // cout << ibc.bridge_size() + 1 << endl;
    for (int i = 0; i < n; i++) {
        if ((int)groups[i].size()) {
            cout << (int)groups[i].size();
            for (auto &u : groups[i]) {
                cout << ' ' << u;
            }
            cout << endl;
        }
    }
}