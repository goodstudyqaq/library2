#include <bits/stdc++.h>
using namespace std;

/*
cnt[i] i 的个数, 返回 g，g[i] 表示两两求 gcd 等于 i 的个数
*/
vector<long long> get_gcd_cnt(vector<int> cnt) {
    int n = cnt.size();
    for (int i = 1; i < n; i++) {
        for (int j = i + i; j < n; j += i) {
            cnt[i] += cnt[j];
        }
    }
    vector<long long> g(n);
    for (int i = 1; i < n; i++) {
        g[i] = 1LL * cnt[i] * (cnt[i] - 1) / 2;
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + i; j < n; j += i) {
            g[i] -= g[j];
        }
    }
    return g;
}