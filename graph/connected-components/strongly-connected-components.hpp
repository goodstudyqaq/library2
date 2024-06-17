#pragma once

/*
Kosaraju 算法
复杂度 O(E + V)
强联通分量：一个强联通分量里的任意两个点两两互达
*/

#include "../graph-template.hpp"

template <typename T = int>
struct StronglyConnectedComponents : Graph<T> {
   public:
    using Graph<T>::Graph;
    using Graph<T>::g;
    vector<int> comp;           // comp[i] i 点在的组 id
    Graph<T> dag;               // 缩点后的图
    vector<vector<int>> group;  // group[i] 表示第 i 组有的点

    void build() {
        int n = g.size();
        rg = Graph<T>(n);
        for (int i = 0; i < n; i++) {
            for (auto &e : g[i]) {
                int u = e.from, v = e.to;
                rg.add_directed_edge(v, u, e.cost);
            }
        }

        used = vector<int>(n, 0);
        comp = vector<int>(n, -1);

        for (int i = 0; i < n; i++) {
            if (used[i] == 0) {
                dfs(i);
            }
        }
        reverse(order.begin(), order.end());

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int u = order[i];
            if (comp[u] == -1) {
                rdfs(u, cnt);
                cnt++;
            }
        }

        dag = Graph<T>(cnt);
        group.resize(cnt);
        for (int i = 0; i < n; i++) {
            for (auto &e : g[i]) {
                int u = comp[e.from], v = comp[e.to];
                if (u == v) continue;
                dag.add_directed_edge(u, v, e.cost);
            }
            group[comp[i]].push_back(i);
        }
    }

    int operator[](int k) const {
        return comp[k];
    }

   private:
    vector<int> order, used;
    Graph<T> rg;

    void dfs(int idx) {
        used[idx] = 1;
        for (auto &e : g[idx]) {
            int v = e.to;
            if (used[v] == 0) {
                dfs(v);
            }
        }
        order.push_back(idx);
    }

    void rdfs(int idx, int cnt) {
        comp[idx] = cnt;
        for (auto &e : rg[idx]) {
            int v = e.to;
            if (comp[v] == -1) {
                rdfs(v, cnt);
            }
        }
    }
};
