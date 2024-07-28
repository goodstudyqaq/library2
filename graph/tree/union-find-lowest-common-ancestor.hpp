#include "../../structure/union-find.hpp"
#include "../graph-template.hpp"
/*
并查集:
遍历完结点 u 的子树后, 将 u 和其父亲所在集合进行合并.
遍历到结点 u 时, 对所有询问 u,v, 若 v 已经被遍历过, 则结 果为 v 所在集合深度最小的结点.
复杂度 O((n + q)α(n)).
离线做法
*/

template <typename T = int>
struct UnionFindLowestCommonAncestor : Graph<T> {
    using Graph<T>::g;
    using Graph<T>::Graph;

    vector<int> build(vector<pair<int, int>> queries, int root = 0) {
        int n = g.size();
        vector<vector<pair<int, int>>> V(n);
        for (int i = 0; i < queries.size(); i++) {
            auto it = queries[i];
            V[it.first].push_back({it.second, i});
            V[it.second].push_back({it.first, i});
        }

        int m = queries.size();
        vector<int> vis(n);
        vector<int> ans(m);
        UnionFind uf(n);
        function<void(int, int)> dfs = [&](int u, int pre) {
            vis[u] = 1;
            for (auto it : V[u]) {
                int v = it.first;
                if (vis[v]) {
                    ans[it.second] = uf.find(v);
                }
            }
            for (auto v : g[u]) {
                if (v == pre) continue;
                dfs(v, u);
            }

            if (pre != -1) {
                uf.unite(u, pre);
            }
        };
        dfs(root, -1);
        return ans;
    }
};
