// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
#include <bits/stdc++.h>

#include "../graph/tree/union-find-lowest-common-ancestor.hpp"

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
    UnionFindLowestCommonAncestor<> lca(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int c;
            cin >> c;
            lca.add_edge(i, c);
        }
    }
    cin >> q;
    vector<pair<int, int>> queries(q);

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        queries[i] = {u, v};
    }
    auto ans = lca.build(queries);
    for (auto it : ans) {
        cout << it << endl;
    }
}