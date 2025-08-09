// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
#include <bits/stdc++.h>

#include "../graph/tree/doubling-lowest-common-ancestor.hpp"

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
    int n, q;
    cin >> n;
    Graph<int> g(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int c;
            cin >> c;
            g.add_edge(i, c);
        }
    }
    DoublingLowestCommonAncestor lca(g);
    lca.build(0);

    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u, v) << endl;
    }
}