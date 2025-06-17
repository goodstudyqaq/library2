// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/general_matching
#include <bits/stdc++.h>

#include "../graph/flow/gabow-edmonds.hpp"

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

    int N, M;
    cin >> N >> M;
    GabowEdmonds flow(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        flow.add_edge(a, b);
    }
    auto ret = flow.max_matching();
    cout << ret.size() << endl;
    for (auto &p : ret) cout << p.first << ' ' << p.second << endl;
}