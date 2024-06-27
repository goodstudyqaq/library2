#include <bits/stdc++.h>
using namespace std;

struct BipartiteMatching {
    vector<vector<int>> graph;
    vector<int> alive, used, match;
    int timestamp;

    explicit BipartiteMatching(int n) : graph(n), alive(n, 1), used(n, 0), match(n, -1), timestamp(0) {}

    void add_edge(int u, int v) {
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    bool augment(int u) {
        used[u] = timestamp;
        for (auto &v : graph[u]) {
            if (alive[v] == 0) continue;
            int to_match = match[v];
            if (to_match == -1 || (used[to_match] != timestamp && augment(to_match))) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int bipartite_matching() {
        int res = 0;
        for (int i = 0; i < (int)graph.size(); i++) {
            if (alive[i] == 0) continue;
            if (match[i] == -1) {
                ++timestamp;
                res += augment(i);
            }
        }
        return res;
    }

    int add_vertex(int idx) {
        alive[idx] = 1;
        ++timestamp;
        return augment(idx);
    }

    int erase_vertex(int idx) {
        // 返回最大匹配的变化量
        alive[idx] = 0;
        if (match[idx] == -1) {
            return 0;
        }
        match[match[idx]] = -1;
        ++timestamp;
        int ret = augment(match[idx]);
        match[idx] = -1;
        return ret - 1;
    }
};