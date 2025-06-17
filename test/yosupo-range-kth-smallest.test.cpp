// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_kth_smallest
#include <bits/stdc++.h>

#include <locale>

#include "../structure/wavelet/wavelet-matrix.hpp"

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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    WaveletMatrix<int> wm(a);
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << wm.quantile(k, l, r) << endl;
    }
    return 0;
}