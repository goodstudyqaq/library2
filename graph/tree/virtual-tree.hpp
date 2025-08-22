#include "../graph-template.hpp"
#include "./doubling-lowest-common-ancestor.hpp"

template <typename T>
struct VirtualTree : Graph<T> {
   public:
    using Graph<T>::Graph;
    using Graph<T>::g;

    Graph<T> build(const vector<int> &points, const int root) {
        DoublingLowestCommonAncestor<T> LCA = DoublingLowestCommonAncestor(g, root);

        timestamp = 0;
        int n = g.size();
        stt.resize(n);
        dfs(root, -1);

        auto p = points;
        sort(p.begin(), p.end(), [&](int x, int y) {
            return stt[x] < stt[y];
        });
        int sz = points.size();
        for (int i = 0; i < sz - 1; i++) {
            p.push_back(LCA.lca(p[i], p[i + 1]));
        }

        sort(p.begin(), p.end(), [&](int x, int y) {
            return stt[x] < stt[y];
        });
        p.resize(unique(p.begin(), p.end()) - p.begin());

        sz = p.size();
        Graph<T> g2(n);
        for (int i = 0; i < sz - 1; i++) {
            int lc = LCA.lca(p[i], p[i + 1]);
            g2.add_edge(lc, p[i + 1]);
        }
        return g2;
    }

   private:
    vector<int> stt;
    int timestamp;
    void dfs(int u, int pre) {
        stt[u] = timestamp++;
        for (auto v : g[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }
    }
};