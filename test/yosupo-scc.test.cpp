
#define PROBLEM "https://judge.yosupo.jp/problem/scc"
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

    cout << scc.group.size() << endl;
    for (int i = 0; i < scc.group.size(); i++) {
        cout << scc.group[i].size();
        for (auto it : scc.group[i]) {
            cout << ' ' << it;
        }
        cout << endl;
    }
    return 0;
}