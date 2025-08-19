/*
找异或值 >= k 距离最小的两点, 沿着 x ^ k 走，如果 k[i] = 0 那么如果 x ^ 1 有点，这个点就是有效的。因为我们需要找距离最小的两点，所以我们就需要维护每个点最大的位置。
*/
#include <bits/stdc++.h>

#include <cstdint>

#include "./structure/others/trie.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

struct Node : public TrieNode {
    int idx;
    Node() {}
    Node(int char_size) : TrieNode(char_size) {}
};

struct BinaryTrie : public Trie<Node> {
    BinaryTrie() : Trie(2, '0') {}
    explicit BinaryTrie(int node_size) : Trie(2, '0', node_size) {}

    void add_number(int x, int idx, int max_bit = 63) {
        int now = root;
        for (int i = max_bit; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (nodes[now].nxt[b] == -1) {
                nodes[now].nxt[b] = new_node();
            }
            now = nodes[now].nxt[b];
            nodes[now].idx = idx;
        }
    }

    int query(int x, int k, int max_bit = 63) {
        int now = root;
        int ans = -1;
        for (int i = max_bit; i >= 0; i--) {
            int kbit = (k >> i) & 1;
            int xbit = (x >> i) & 1;
            if (kbit == 0) {
                if (nodes[now].nxt[xbit ^ 1] != -1) {
                    int go = nodes[now].nxt[xbit ^ 1];
                    ans = max(ans, nodes[go].idx);
                }
            }
            if (nodes[now].nxt[xbit ^ kbit] == -1) {
                return ans;
            }
            int go = nodes[now].nxt[xbit ^ kbit];
            now = go;
        }
        ans = max(ans, nodes[now].idx);
        return ans;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int ans = 1e9;
    const int MAX_BIT = 30;
    BinaryTrie bt(n * MAX_BIT + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        bt.add_number(a[i], i, MAX_BIT - 1);
        int res = bt.query(a[i], k, MAX_BIT - 1);
        if (res != -1) {
            ans = min(ans, i - res + 1);
        }
    }
    if (ans == 1e9) ans = -1;
    cout << ans << '\n';
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}