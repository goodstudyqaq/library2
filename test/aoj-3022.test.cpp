#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3022"

#include <bits/stdc++.h>

#include "../graph/others/block-cut-tree.hpp"

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
    vector<long long> w(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        sum += w[i];
    }

    BlockCutTree<int> bct(n);
    bct.read(m);
    bct.build();

    vector<long long> ans(n);
    auto &articulation = bct.articulation;

    vector<long long> sum2(bct.group.size());
    for (int i = 0; i < bct.group.size(); i++) {
        for (auto &u : bct.group[i]) {
            sum2[i] += w[u];
        }
    }

    auto &g = bct.tree;

    vector<long long> sum3(bct.group.size());
    vector<long long> dp(bct.group.size());
    function<void(int, int)> dfs = [&](int u, int pre) {
        sum3[u] = sum2[u];
        for (auto &v : g[u]) {
            if (v == pre) continue;
            dfs(v, u);
            dp[u] = max(dp[u], sum3[v]);
            sum3[u] += sum3[v];
        }
    };
    dfs(0, -1);

    for (auto &u : articulation) {
        ans[u] = max(dp[bct[u]], sum - sum3[bct[u]]);
    }

    for (int i = 0; i < n; i++) {
        if (ans[i] == 0) {
            ans[i] = sum - w[i];
        }
        cout << ans[i] << endl;
    }
    return 0;
}