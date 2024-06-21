#pragma once
/*
点双连通：在一张连通的无向图中，对于两个点 u 和 v，如果无论删去哪个点（只能删去一个，且不能删 u 和 v 自己）都不能使它们不连通，我们就说 u 和 v 点双连通。
*/
#include "../graph-template.hpp"
#include "../others/low-link.hpp"

template <typename T = int>
struct BiConnectedComponents : LowLink<T> {
   public:
    using LowLink<T>::LowLink;
    using LowLink<T>::g;
    using LowLink<T>::dfn;
    using LowLink<T>::low;

    vector<vector<Edge<T>>> bc;

    void build() override {
        LowLink<T>::build();
        vis.assign(g.size(), 0);
        for (int i = 0; i < g.size(); i++) {
            if (vis[i] == 0) {
                dfs(i, -1);
            }
        }
    }

    explicit BiConnectedComponents(const Graph<T> &g) : Graph<T>(g) {}

   private:
    vector<int> vis;
    vector<Edge<T>> tmp;

    void dfs(int u, int pre) {
        vis[u] = 1;
        bool beet = false;  // beet 检查是否有跟父亲的重边
        for (auto &v : g[u]) {
            if (v == pre && exchange(beet, true) == false) continue;
            if (!vis[v] || dfn[v] < dfn[u]) {  // dfn[v] < dfn[u] 感觉只有跟父亲有重边时会加进来
                tmp.emplace_back(v);
            }

            if (!vis[v]) {
                dfs(v, u);
                if (low[v] >= dfn[u]) {
                    bc.emplace_back();
                    while (true) {
                        auto e = tmp.back();
                        bc.back().emplace_back(e);
                        tmp.pop_back();
                        if (v.idx == e.idx) break;
                    }
                }
            }
        }
    }
};
