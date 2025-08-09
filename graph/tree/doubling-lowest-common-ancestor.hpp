#pragma once
#include "../graph-template.hpp"
/*
树上倍增找 lca
*/

template <typename T = int>
struct DoublingLowestCommonAncestor {
    explicit DoublingLowestCommonAncestor() {}

    explicit DoublingLowestCommonAncestor(const Graph<T> &g, int root = 0) : g(g) {
        build(root);
    }

    void build(int root = 0) {
        LOG = 32 - __builtin_clz(g.size());
        dep.assign(g.size(), 0);
        sum.assign(g.size(), 0);
        table.assign(LOG, vector<int>(g.size(), -1));
        dfs(root, -1, 0);
        for (int k = 0; k + 1 < LOG; k++) {
            for (int i = 0; i < (int)table[k].size(); i++) {
                if (table[k][i] == -1)
                    table[k + 1][i] = -1;
                else
                    table[k + 1][i] = table[k][table[k][i]];
            }
        }
    }

    int lca(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        v = climb(v, dep[v] - dep[u]);
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (table[i][u] != table[i][v]) {
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }

    int climb(int u, int k) {
        if (dep[u] < k) return -1;
        for (int i = LOG - 1; i >= 0; i--) {
            if ((k >> i) & 1) u = table[i][u];
        }
        return u;
    }

    T dist(int u, int v) { return sum[u] + sum[v] - 2 * sum[lca(u, v)]; }

   private:
    vector<int> dep;
    vector<T> sum;
    vector<vector<int> > table;
    int LOG;
    const Graph<T> &g;

    void dfs(int idx, int par, int d) {
        table[0][idx] = par;
        dep[idx] = d;
        for (auto &to : g[idx]) {
            if (to != par) {
                sum[to] = sum[idx] + to.cost;
                dfs(to, idx, d + 1);
            }
        }
    }
};