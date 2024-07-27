#include "../../structure/others/sparse-table.hpp"
#include "../graph-template.hpp"
/*
有点奇怪的写法，记录 dfs 时经过的每个点到 ord 里，维护每个点第一次在 ord 里的下标 in，求两个点的 lca 等价于ord 里 [in[a], in[b]] 中 dep 最小的那个点。感觉很合理。
*/

template <typename T = int>
struct RMQLowestCommonAncestor : Graph<T> {
   public:
    using Graph<T>::Graph;
    using Graph<T>::g;
    using F = function<int(int, int)>;

    void build(int root = 0) {
        ord.reserve(g.size() * 2 - 1);
        dep.reserve(g.size() * 2 - 1);
        in.resize(g.size());
        dfs(root, -1, 0);
        vector<int> vs(g.size() * 2 - 1);
        iota(begin(vs), end(vs), 0);
        F f = [&](int a, int b) { return dep[a] < dep[b] ? a : b; };
        st = get_sparse_table(vs, f);
    }

    int lca(int x, int y) const {
        if (in[x] > in[y]) swap(x, y);
        return x == y ? x : ord[st.fold(in[x], in[y])];
    }

   private:
    vector<int> ord, dep, in;
    SparseTable<int, F> st;

    void dfs(int idx, int par, int d) {
        in[idx] = (int)ord.size();
        ord.emplace_back(idx);
        dep.emplace_back(d);
        for (auto &to : g[idx]) {
            if (to != par) {
                dfs(to, idx, d + 1);
                ord.emplace_back(idx);
                dep.emplace_back(d);
            }
        }
    }
};