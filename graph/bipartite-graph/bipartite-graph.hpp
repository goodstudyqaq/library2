#include "../../structure/union-find/union-find.hpp"
#include "../graph-template.hpp"
/*
二分图染色，判断一个图是否是二分图
//https://codeforces.com/contest/1991/problem/E
*/

template <typename T = int>
struct BipartiteGraph : Graph<T> {
    using Graph<T>::Graph;
    using Graph<T>::size;
    UnionFind uf;
    vector<int> _color;

    explicit BipartiteGraph(int n) : Graph<T>(n), uf(2 * n), _color(2 * n, -1) {}

    void add_edge(int from, int to, T cost = 1) {
        Graph<T>::add_edge(from, to, cost);
        uf.unite(from, to + size());
        uf.unite(to, from + size());
    }

    bool bipartite_graph_coloring() {
        int n = size();
        for (int i = 0; i < n; i++) {
            int a = uf.find(i);
            int b = uf.find(i + n);
            if (a == b) return false;
            if (_color[a] < 0) _color[a] = 0, _color[b] = 1;
        }
        return true;
    }

    int color(int u) {
        return _color[uf.find(u)];
    }
};