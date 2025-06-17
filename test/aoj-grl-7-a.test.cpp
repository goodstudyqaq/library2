// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A
#include <bits/stdc++.h>

#include "../graph/flow/bipartite-matching.hpp"

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
    int x, y, e;
    cin >> x >> y >> e;
    BipartiteMatching bm(x + y);
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        bm.add_edge(a, x + b);
    }
    cout << bm.bipartite_matching() << endl;
}