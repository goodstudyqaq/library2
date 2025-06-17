#include <limits>
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/segment_add_get_min
#include <bits/stdc++.h>

#include "../structure/segment-tree/dynamic-li-chao-segment-tree.hpp"

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
    cin >> n >> q;
    const long long inf = numeric_limits<long long>::max() / 2;
    DynamicLiChaoSegmentTree<long long, -1000000000, 1000000000, inf> dlct;

    for (int i = 0; i < n; i++) {
        long long l, r, a, b;
        cin >> l >> r >> a >> b;
        dlct.add_segment(l, r, a, b);
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            long long l, r, a, b;
            cin >> l >> r >> a >> b;
            dlct.add_segment(l, r, a, b);
        } else {
            long long p;
            cin >> p;
            auto ret = dlct.query(p);
            if (ret >= inf) {
                cout << "INFINITY\n";
            } else {
                cout << ret << endl;
            }
        }
    }
}