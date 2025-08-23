#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
/*
char* 1-bas
sum[i] = s[1] * Seed ^ 1 + s[2] * Seed ^ 2 + ... s[i] * Seed ^ i
*/
struct Hash {
    ULL Seed, Mod;
    string s;
    vector<ULL> bas, sum;
    vector<int> perm;

    int char_size, margin;
    Hash() {}

    // int perm[sigma];
    Hash(ULL Seed, ULL Mod, const string &_s, int _char_size, int _margin) : Seed(Seed), Mod(Mod), s(_s), char_size(_char_size), margin(_margin) {
        int n = s.size();
        bas.resize(n + 1);
        sum.resize(n + 1);
        perm.resize(char_size);
        iota(perm.begin(), perm.end(), 0);
        // random_shuffle(perm.begin(), perm.end());
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(perm.begin(), perm.end(), g);
        init();
    }
    void init() {
        bas[0] = 1;
        int n = s.size();
        for (int i = 1; i <= n; i++) {
            bas[i] = bas[i - 1] * Seed % Mod;
            sum[i] = (sum[i - 1] + (s[i - 1] - margin) * bas[i] % Mod) % Mod;
        }
    }
    /*random_shuffle 离散化id，防止kill_hash*/
    void indexInit() {
        bas[0] = 1;
        int n = s.size();
        for (int i = 1; i <= n; i++) {
            bas[i] = bas[i - 1] * Seed % Mod;
            sum[i] = (sum[i - 1] + perm[s[i - 1] - margin] * bas[i] % Mod) % Mod;
        }
    }
    ULL getHash(int l, int r) {
        l++, r++;
        return (sum[r] - sum[l - 1]) * bas[s.size() - l];
    }
};
const int HASH_CNT = 2;
ULL Seed_Pool[] = {911, 146527, 19260817, 91815541};
ULL Mod_Pool[] = {29123, 998244353, 1000000009, 4294967291ull};

struct HashHandler {
    vector<Hash> hasher;
    HashHandler(const string &s, int char_size, int margin) {
        hasher.resize(HASH_CNT);
        for (int i = 0; i < HASH_CNT; i++) {
            hasher[i] = Hash(Seed_Pool[i], Mod_Pool[i], s, char_size, margin);
            hasher[i].indexInit();  // or hasher[i].init();
        }
    }

    vector<ULL> getHash(int l, int r) {
        vector<ULL> ans(HASH_CNT);
        for (int i = 0; i < HASH_CNT; i++) {
            ans[i] = hasher[i].getHash(l, r);
        }
        return ans;
    }
    bool equal(const vector<ULL> &h1, const vector<ULL> &h2) {
        assert(h1.size() == h2.size());
        for (int i = 0; i < h1.size(); i++) {
            if (h1[i] != h2[i]) return false;
        }
        return true;
    }
};
