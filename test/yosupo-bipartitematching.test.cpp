// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bipartitematching
#include <bits/stdc++.h>

#include "../graph/flow/bipartite-flow.hpp"

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

    int L, R, M;
    cin >> L >> R >> M;
    BipartiteFlow flow(L, R);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        flow.add_edge(a, b);
    }
    auto es = flow.max_matching();
    cout << es.size() << "\n";
    for (auto &p : es) cout << p.first << " " << p.second << "\n";
}