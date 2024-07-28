#include "../graph-template.hpp"
template <typename T = int>
struct HeavyLightDecomposition : Graph<T> {
   public:
    using Graph<T>::Graph;
    using Graph<T>::g;
    /*
        sz[u]: u 子树大小
        par[u]: u 的父亲
        dep[u]: u 的深度
        in[u]: dfs 序 u 进来的时间戳
        out[u]: dfs 序 u 出去的时间戳
        head[u]: u 所在的重链的起始位置
        rev[t]: 时间戳为 t 时对应的节点
    */
    vector<int> sz, in, out, head, rev, par, dep;

    void build(int root = 0) {
        sz.assign(g.size(), 0);
        in.assign(g.size(), 0);
        out.assign(g.size(), 0);
        head.assign(g.size(), 0);
        rev.assign(g.size(), 0);
        par.assign(g.size(), 0);
        dep.assign(g.size(), 0);

        dfs_sz(root, -1, 0);
        int t = 0;
        head[root] = root;
        dfs_hld(root, -1, t);
    }

    int lca(int u, int v) const {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return u;
        }
    }

   private:
    void dfs_sz(int u, int pre, int d) {
        dep[u] = d;
        par[u] = pre;
        sz[u] = 1;
        if (g[u].size() && g[u][0] == pre) swap(g[u][0], g[u].back());
        for (auto &v : g[u]) {
            if (v == pre) continue;
            dfs_sz(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[g[u][0]] < sz[v]) swap(g[u][0], v);
        }
    }

    void dfs_hld(int u, int pre, int &times) {
        in[u] = times++;
        rev[in[u]] = u;
        for (auto &v : g[u]) {
            if (v == pre) continue;
            head[v] = (g[u][0] == v ? head[u] : v);
            dfs_hld(v, u, times);
        }
        out[u] = times;
    }
};