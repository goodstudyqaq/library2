#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"
#include <bits/stdc++.h>

#include "../graph/others/low-link.hpp"

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
    LowLink<int> g(n);
    g.read(m, 0);
    g.build();

    auto &art = g.articulation;
    sort(art.begin(), art.end());
    for (auto &v : art) {
        cout << v << endl;
    }
}