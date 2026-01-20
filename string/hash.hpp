#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
/*
char* 1-bas
sum[i] = s[1] * Seed ^ 1 + s[2] * Seed ^ 2 + ... s[i] * Seed ^ i

*/
struct Hash {
    long long Seed, Mod;
    string s;
    vector<long long> bas, sum;
    vector<int> perm;

    int char_size, margin;
    Hash() {}

    // int perm[sigma];
    Hash(long long Seed, long long Mod, const string& _s, int _char_size, int _margin) : Seed(Seed), Mod(Mod), s(_s), char_size(_char_size), margin(_margin) {
        int n = s.size();
        bas.resize(n + 1);
        sum.resize(n + 1);
        perm.resize(char_size);
        iota(perm.begin(), perm.end(), 1);
        // random_shuffle(perm.begin(), perm.end());
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(perm.begin(), perm.end(), g);
        // init();
    }
    void init() {
        bas[0] = 1;
        int n = s.size();
        for (int i = 1; i <= n; i++) {
            bas[i] = bas[i - 1] * Seed % Mod;
            sum[i] = (sum[i - 1] + (s[i - 1] - margin + 1) * bas[i] % Mod) % Mod;
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
    long long getHash(int l, int r) {
        l++, r++;
        return ((sum[r] - sum[l - 1]) % Mod + Mod) % Mod * bas[s.size() - l] % Mod;
    }
};
const int HASH_CNT = 2;
long long Seed_Pool[] = {307, 311, 313, 317, 331, 337, 347, 349};
long long Mod_Pool[] = {998244353, 998244389, 998244391, 998244397,
                        998244407, 998244431, 998244433, 998244473};

struct HashHandler {
    vector<Hash> hasher;
    HashHandler(const string& s, int char_size, int margin) {
        hasher.resize(HASH_CNT);
        for (int i = 0; i < HASH_CNT; i++) {
            hasher[i] = Hash(Seed_Pool[i], Mod_Pool[i], s, char_size, margin);
            hasher[i].indexInit();  // or hasher[i].init();
        }
    }

    long long getHash(int l, int r) {
        long long ans = 0;
        for (int i = 0; i < HASH_CNT; i++) {
            ans = (ans << 32) ^ hasher[i].getHash(l, r);
        }
        return ans;
    }
};