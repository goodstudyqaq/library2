#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C"
#include <bits/stdc++.h>

#include "../graph/connected-components/strongly-connected-components.hpp"

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
    StronglyConnectedComponents<int> scc(n);
    scc.read(m, 0, false, true);
    scc.build();
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << (scc[u] == scc[v]) << endl;
    }
    return 0;
}