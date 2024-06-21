/*
https://oi-wiki.org/graph/cut/
割点和桥
1. 割点：对于无向图，如果把一个点删除后这个图的极大连通分量数增加了，那么这个点就是这个图的割点（又称割顶）。
2. 极大连通分量：无向图中，能够互相到达的点在一个极大联通分量当中
3. 桥：对于无向图来说，删掉一个边后，连通分量增加了，那么这个就是桥
*/
#include "../graph-template.hpp"
template <typename T = int>
struct LowLink : Graph<T> {
   public:
    using Graph<T>::Graph;
    vector<int> dfn, low;      // dfn[i]: i 点的时间戳, low[i]: i 点不经过父亲能到达的最小时间戳
    vector<int> articulation;  // 存割点
    vector<Edge<T>> bridge;    // 存桥
    using Graph<T>::g;

    virtual void build() {
        vis.assign(g.size(), 0);
        dfn.assign(g.size(), 0);
        low.assign(g.size(), 0);

        inde = 0;
        for (int i = 0; i < g.size(); i++) {
            if (!vis[i]) dfs(i, -1);
        }
    }

    explicit LowLink(const Graph<T> &g) : Graph<T>(g) {}

   private:
    vector<int> vis;
    int inde;

    void dfs(int u, int pre) {
        vis[u] = 1;
        dfn[u] = low[u] = inde++;
        int child = 0;
        bool is_articulation = false, beet = false;  // beet 检查是否有跟父亲的重边
        for (auto &v : g[u]) {
            if (v == pre && !exchange(beet, true)) {  // 如果 v = pre，那么第一次会被 continue 掉，而之后就会继续往下走
                continue;
            }
            if (!vis[v]) {
                child++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                is_articulation |= (pre >= 0 && low[v] >= dfn[u]);  // 首先这里判断的点不能是第一个进来的节点，只要有一个 v 的 low[v] >= dfn[u] 那么 u 就是割点
                if (low[v] > dfn[u]) {
                    // 如果 low[v] > dfn[u] 说明这个边是桥
                    bridge.emplace_back(v);
                }

            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }

        is_articulation |= (pre == -1 && child > 1);  // 如果它是第一个进来的点，且它有 2 个 child，那么它就是割点
        if (is_articulation) articulation.push_back(u);
    }
};
