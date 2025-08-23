#include <bits/stdc++.h>

#include "./math/mint.hpp"
using namespace std;
/*
sum[i][j] = sum[i - 1][j - 1] - sum[i - 1][j] - sum[i][j - 1] + s[i][j] * base1^i * base2^j
*/

typedef unsigned long long ULL;
ULL Seed_Pool[] = {911, 146527, 19260817, 91815541};

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

struct Hash {
    ULL Seed1, Seed2;
    vector<string> s;
    vector<Mint> base1, base2;
    vector<vector<Mint>> sum;
    vector<int> perm;
    int char_size, margin;
    Hash() {}

    Hash(ULL Seed1, ULL Seed2, const vector<string>& s, int char_size, int margin) : Seed1(Seed1), Seed2(Seed2), s(s), char_size(char_size), margin(margin) {
        int n = s.size(), m = s[0].size();
        base1.resize(n + 1);
        base2.resize(m + 1);
        sum.resize(n + 1, vector<Mint>(m + 1));
        perm.resize(char_size);
        iota(perm.begin(), perm.end(), 0);

        // std::random_device rd;
        // std::mt19937 g(rd());
        // shuffle(perm.begin(), perm.end(), g);
        indexInit();
    }

    void indexInit() {
        base1[0] = 1;
        base2[0] = 1;
        int n = s.size();
        for (int i = 1; i <= n; i++) {
            base1[i] = base1[i - 1] * Seed1;
        }
        int m = s[0].size();
        for (int i = 1; i <= m; i++) {
            base2[i] = base2[i - 1] * Seed2;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + Mint(perm[s[i - 1][j - 1] - margin]) * base1[i - 1] * base2[j - 1];
            }
        }
    }

    Mint getHash(int x1, int y1, int x2, int y2) {
        int n = s.size();
        int m = s[0].size();
        x1++, y1++, x2++, y2++;
        Mint res = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
        return res * base1[n - x1] * base2[m - y1];
    }
};