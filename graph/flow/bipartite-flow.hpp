/*
二分图
*/
#include <bits/stdc++.h>

#include <cstddef>
#include <queue>
using namespace std;

struct BipartiteFlow {
    size_t n, m, time_stamp;
    vector<vector<int>> g, rg;
    vector<int> match_l, match_r, dist, used, alive;
    bool matched;

   public:
    explicit BipartiteFlow(size_t n, size_t m) : n(n), m(m), time_stamp(0), g(n), rg(m), match_l(n, -1), match_r(m, -1), used(n), alive(n, 1), matched(false) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    void erase_edge(int a, int b) {
        if (match_l[a] == b) {
            match_l[a] = -1;
            match_r[b] = -1;
        }
        g[a].erase(find(g[a].begin(), g[a].end(), b));
        rg[b].erase(find(rg[b].begin(), rg[b].end(), a));
    }

    vector<pair<int, int>> max_matching() {
        // 最大匹配
        matched = true;
        for (;;) {
            build_augment_path();

            ++time_stamp;
            int flow = 0;
            for (int i = 0; i < (int)n; i++) {
                if (match_l[i] == -1) flow += find_min_dist_argument_dist(i);
            }
            if (flow == 0) break;
        }
        vector<pair<int, int>> ans;
        for (int i = 0; i < (int)n; i++) {
            if (match_l[i] >= 0) ans.emplace_back(i, match_l[i]);
        }
        return ans;
    }

    vector<int> min_vertex_cover() {
        // 最小顶点覆盖, 最小点覆盖=最大匹配数，这里输出方案
        // https://www.cnblogs.com/C202202chenkelin/p/14437260.html
        auto visited = find_residual_path();
        vector<int> ans;
        for (int i = 0; i < (int)(n + m); i++) {
            if (visited[i] ^ (i < (int)n)) {  // 左边没有被标记，右边被标记的点会被选中
                ans.emplace_back(i);
            }
        }
        return ans;
    }

    vector<pair<int, int>> lex_max_matching() {
        // 返回字典序最小的最大匹配
        if (!matched) max_matching();
        for (auto &vs : g) sort(begin(vs), end(vs));
        vector<pair<int, int>> es;
        for (int i = 0; i < (int)n; i++) {
            if (match_l[i] == -1 || alive[i] == 0) {
                continue;
            }
            match_r[match_l[i]] = -1;
            match_l[i] = -1;
            ++time_stamp;
            find_augment_path(i);
            alive[i] = 0;
            es.emplace_back(i, match_l[i]);
        }
        return es;
    }

    vector<int> lex_min_vertex_cover(const vector<int> &ord) {
        // todo:
    }

    vector<int> max_independent_set() {
        // 最大独立集 = 所有点 - 最小点覆盖
        auto visited = find_residual_path();
        vector<int> ans;
        for (int i = 0; i < (int)(n + m); i++) {
            if (visited[i] ^ (i >= (int)n)) {
                ans.emplace_back(i);
            }
        }
        return ans;
    }

    vector<pair<int, int>> min_edge_cover() {
        // 最小边覆盖 = n + m - 最大匹配
        auto es = max_matching();
        for (int i = 0; i < (int)n; i++) {
            if (match_l[i] >= 0) {
                continue;
            }
            if (g[i].empty()) {
                return {};
            }
            es.emplace_back(i, g[i][0]);
        }
        for (int i = 0; i < (int)m; i++) {
            if (match_r[i] >= 0) {
                continue;
            }
            if (g[i].empty()) {
                return {};
            }
            es.emplace_back(rg[i][0], i);
        }
        return es;
    }

    vector<vector<int>> build_residual_graph() {
        // 构造残留网络
        // 残留网络讲解：https://seineo.github.io/%E5%9B%BE%E8%AE%BA%EF%BC%9A%E6%9C%80%E5%A4%A7%E6%B5%81%E6%9C%80%E5%B0%8F%E5%89%B2%E8%AF%A6%E8%A7%A3.html
        if (!matched) max_matching();
        const size_t S = n + m;
        const size_t T = S + 1;
        vector<vector<int>> ris(n + m + 2);
        for (int i = 0; i < (int)n; i++) {
            if (match_l[i] == -1) {
                ris[S].emplace_back(i);
            } else {
                ris[i].emplace_back(S);
            }
        }

        // 这一段对找最小顶点覆盖没用？
        for (int i = 0; i < (int)m; i++) {
            if (match_r[i] == -1) {
                ris[i + n].emplace_back(T);
            } else {
                ris[T].emplace_back(i + n);
            }
        }

        for (int i = 0; i < (int)n; i++) {
            for (auto &j : g[i]) {
                if (match_l[i] == j) {
                    ris[j + n].emplace_back(i);
                } else {
                    ris[i].emplace_back(j + n);
                }
            }
        }
        return ris;
    }

   private:
    bool find_augment_path(int a) {
        used[a] = time_stamp;
        for (auto &b : g[a]) {
            int c = match_r[b];
            if (c < 0 || (alive[c] == 1 && used[c] != (int)time_stamp && find_augment_path(c))) {
                match_r[b] = a;
                match_l[a] = b;
                return true;
            }
        }
        return false;
    }

    vector<int> find_residual_path() {
        auto res = build_residual_graph();
        queue<int> Q;
        vector<int> visited(n + m + 2);
        int s = n + m;
        Q.emplace(s);
        visited[s] = 1;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto &v : res[u]) {
                if (visited[v]) continue;
                visited[v] = 1;
                Q.emplace(v);
            }
        }
        return visited;
    }

    bool find_min_dist_argument_dist(int a) {
        used[a] = time_stamp;
        for (auto &b : g[a]) {
            int c = match_r[b];
            if (c < 0 || (used[c] != (int)time_stamp && dist[c] == dist[a] + 1 && find_min_dist_argument_dist(c))) {
                match_l[a] = b;
                match_r[b] = a;
                return true;
            }
        }
        return false;
    }

    void build_augment_path() {
        // 找增广路
        queue<int> que;
        dist.assign(g.size(), -1);
        for (int i = 0; i < (int)n; i++) {
            if (match_l[i] == -1) {
                que.emplace(i);
                dist[i] = 0;
            }
        }

        while (!que.empty()) {
            int a = que.front();
            que.pop();
            for (auto &b : g[a]) {
                int c = match_r[b];
                if (c >= 0 && dist[c] == -1) {
                    dist[c] = dist[a] + 1;
                    que.emplace(c);
                }
            }
        }
    }
};