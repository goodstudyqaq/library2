#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"
#include <bits/stdc++.h>

#include "../structure/segment-tree/segment-tree.hpp"

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
struct Info {
    // 默认值
    int x;
    Info(int _x = INT_MAX) {
        x = _x;
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) { return Info(min(left_info.x, right_info.x)); };
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;
    SegmentTree<Info> seg(n);
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 0) {
            seg.assign(x, Info(y));
        } else {
            cout << seg.rangeQuery(x, y + 1).x << endl;
        }
    }
    return 0;
}