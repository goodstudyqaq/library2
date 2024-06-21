/*
在线维护边双联通分量
https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity
*/
#pragma once
#include "../../structure/union-find.hpp"

struct IncrementalBridgeConnectivity {
   public:
    IncrementalBridgeConnectivity() = default;
    explicit IncrementalBridgeConnectivity(int sz) : cc(sz), bcc(sz), fa(sz, sz), bridge(0) {}
    int find(int x) {
        return bcc.find(x);
    }
    size_t bridge_size() const {
        return bridge;
    }

    void add_edge(int x, int y) {
        x = bcc.find(x), y = bcc.find(y);
        if (cc.find(x) == cc.find(y)) {
            int w = lca(x, y);
            compress(x, w);
            compress(y, w);
        } else {
            // 不在同一个强联通分量当中
            if (cc.size(x) > cc.size(y)) swap(x, y);
            link(x, y);
            cc.unite(x, y);
            bridge++;
        }
    }

   private:
    UnionFind cc, bcc;  // cc 是否现在在同一个强联通分量中，bcc 是否在同一个边双联通分量重
    vector<int> fa;     // 根据边双联通分量缩点后 fa[i] i 点的父亲，如果 fa[i] = sz 则 i 没有父亲
    size_t bridge;      // 桥的个数

    int size() {
        return fa.size();
    }

    int par(int x) {
        if (fa[x] == size()) return size();  // 没有父亲
        return bcc.find(fa[x]);
    }

    int lca(int x, int y) {
        // 相当于 x 往上走一步，y 往上走一步，记录路径经过的点，第一个被经过 2 次的点就是 lca
        unordered_set<int> vis;
        while (true) {
            if (x != size()) {                        // 判断 x 是否是无效点
                if (!vis.insert(x).second) return x;  // second 返回一个 bool 值，表示是否插入成功，如果没成功，说明之前已经插入这个点
                x = par(x);
            }
            swap(x, y);
        }
    }

    void compress(int x, int y) {
        while (bcc.find(x) != bcc.find(y)) {
            int nxt = par(x);
            fa[x] = fa[y];
            bcc.unite(x, y);
            x = nxt;
            bridge--;
        }
    }

    void link(int x, int y) {
        int v = x, pre = y;
        while (v != size()) {
            int nxt = par(v);
            fa[v] = pre;
            pre = v;
            v = nxt;
        }
    }
};