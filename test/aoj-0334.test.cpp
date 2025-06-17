// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0334
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

    int n;
    cin >> n;
    n--;

    BipartiteFlow flow(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int b;
            cin >> b;
            if (b) flow.add_edge(j, i);
        }
    }

    auto v = flow.lex_max_matching();
    if (v.size() < n) {
        cout << "no" << endl;
    } else {
        cout << "yes" << endl;
        for (auto &p : v) {
            cout << p.second + 1 << endl;
        }
    }
}