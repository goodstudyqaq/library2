// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3198
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
    int N, M, Q;
    cin >> N >> M;
    BipartiteFlow flow(N, N);
    set<pair<int, int> > mas;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        mas.emplace(a, b);
        flow.add_edge(a, b);
    }
    cin >> Q;
    while (Q--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        if (mas.count({a, b})) {
            mas.erase({a, b});
            flow.erase_edge(a, b);
        } else {
            mas.emplace(a, b);
            flow.add_edge(a, b);
        }
        if (flow.max_matching().size() == N) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}