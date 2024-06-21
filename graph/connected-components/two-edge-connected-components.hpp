/*
边双连通分量: 在一张连通的无向图中，对于两个点 u 和 v，如果无论删去哪条边（只能删去一条）都不能使它们不连通，我们就说 u 和 v 边双连通。
*/
#pragma once

#include "../others/low-link.hpp"

template <typename T = int>
struct TwoEdgeConnectedComponents : LowLink<T> {
   public:
    using LowLink<T>::LowLink;
    using LowLink<T>::g;
    using LowLink<T>::dfn;
    using LowLink<T>::low;
    using LowLink<T>::bridge;

    vector<int> belong;         // belong[i] i 点属于的组
    Graph<T> tree;              // 缩点后的树
    vector<vector<int>> group;  // group[i] i 组所拥有的点集

    void build() override {
        LowLink<T>::build();
        belong.assign(g.size(), -1);
        int k = 0;
        for (int i = 0; i < (int)g.size(); i++) {
            if (belong[i] == -1) {
                dfs(i, -1, k);
            }
        }
        group.resize(k);
        for (int i = 0; i < (int)g.size(); i++) {
            group[belong[i]].emplace_back(i);
        }

        tree = Graph<T>(k);
        for (auto &e : bridge) {
            tree.add_edge(belong[e.from], belong[e.to], e.cost);
        }
    }

    explicit TwoEdgeConnectedComponents(const Graph<T> &g) : Graph<T>(g) {}

   private:
    void dfs(int u, int pre, int &k) {
        if (pre >= 0 && dfn[pre] >= low[u]) {
            belong[u] = belong[pre];
        } else {
            belong[u] = k++;
        }
        for (auto &v : g[u]) {
            if (belong[v] == -1) {
                dfs(v, u, k);
            }
        }
    }
};