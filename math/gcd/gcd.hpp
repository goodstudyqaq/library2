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

/*
返回与 a[i] 互质的个数
*/
vector<int> get_prm_cnt(const vector<int> &a, int m) {
    int n = a.size();
    vector<int> cnt(m + 1);
    for (int i = 0; i < n; i++) {
        cnt[a[i]]++;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = i + i; j <= m; j += i) {
            cnt[i] += cnt[j];
        }
    }

    auto get_prm = [&](int val) {
        vector<int> prm;
        for (int i = 2; i <= sqrt(val); i++) {
            if (val % i == 0) {
                prm.push_back(i);
                while (val % i == 0) {
                    val /= i;
                }
            }
        }
        if (val != 1) {
            prm.push_back(val);
        }
        return prm;
    };

    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        int val = a[i];

        if (val == 1) {
            dp[i] = n - 1;
            continue;
        }

        vector<int> prm = get_prm(val);

        int sz = prm.size();
        const int LIMIT = 1 << sz;
        for (int j = 0; j < LIMIT; j++) {
            int num = 1;
            int one_num = 0;
            for (int k = 0; k < sz; k++) {
                if ((j >> k) & 1) {
                    num *= prm[k];
                    one_num++;
                }
            }
            if (one_num % 2 == 0) {
                dp[i] += cnt[num];
            } else {
                dp[i] -= cnt[num];
            }
        }
    }
    return dp;
}
