// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_set_path_composite
#include <bits/stdc++.h>

#include "../graph/tree/heavy-light-decomposition.hpp"
#include "../math/mint.hpp"
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

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

struct Info {
    // 默认值
    Mint a, b;
    Info(Mint a = 1, Mint b = 0) : a(a), b(b) {}
    static Info merge(const Info& left_info, const Info& right_info, int l = 0, int r = 0) {
        // a, b -> right_info(left_info)
        Mint a = left_info.a * right_info.a;
        Mint b = right_info.a * left_info.b + right_info.b;

        return Info(a, b);
    }
    string to_string() {
        return "";
    }
};

struct Info2 {
    // 默认值
    Mint a, b;
    Info2(Mint a = 1, Mint b = 0) : a(a), b(b) {}
    static Info2 merge(const Info2& left_info, const Info2& right_info, int l = 0, int r = 0) {
        // a, b -> left(right)
        Mint a = left_info.a * right_info.a;
        Mint b = left_info.a * right_info.b + left_info.b;

        return Info2(a, b);
    }
    string to_string() {
        return "";
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    SegmentTree<Info> st(n);
    SegmentTree<Info2> rev_st(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    HeavyLightDecomposition<> hld(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }

    hld.build();
    // debug(hld.rev);

    for (int i = 0; i < n; i++) {
        int u = hld.rev[i];
        st.assign(i, Info(a[u], b[u]));
        rev_st.assign(i, Info2(a[u], b[u]));
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, c, d;
            cin >> p >> c >> d;
            int timestamp = hld.in[p];
            st.assign(timestamp, Info(c, d));
            rev_st.assign(timestamp, Info2(c, d));
        } else {
            int u, v, x;
            cin >> u >> v >> x;
            Info res;
            auto route = hld.dec(u, v);
            for (auto [u, v, flag] : route) {
                if (flag) {
                    Info2 tmp = rev_st.rangeQuery(u, v + 1);
                    res = Info::merge(res, Info(tmp.a, tmp.b));
                } else {
                    Info tmp = st.rangeQuery(u, v + 1);
                    res = Info::merge(res, tmp);
                }
            }
            cout << res.a * x + res.b << endl;
        }
    }
    return 0;
}