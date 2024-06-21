#pragma once
/*
https://ei1333.hateblo.jp/entry/2020/03/25/010057
BlockCutTree: 用割点和不同的点双联通分量相连得到的树
*/
#include "../connected-components/bi-connectd-components.hpp"

template <typename T = int>
struct BlockCutTree : BiConnectedComponents<T> {
   public:
    using BiConnectedComponents<T>::BiConnectedComponents;
    using BiConnectedComponents<T>::g;
    using BiConnectedComponents<T>::articulation;
    using BiConnectedComponents<T>::bc;

    vector<int> belong;         // belong[i] 表示 i 点属于哪个组
    vector<vector<int>> group;  // group[i] 表示 i 组里包含的点
    Graph<T> tree;

    explicit BlockCutTree(const Graph<T> &g) : Graph<T>(g) {}

    int operator[](const int &k) const { return belong[k]; }

    void build() override {
        BiConnectedComponents<T>::build();
        belong.assign(g.size(), -1);
        int ptr = bc.size();
        for (auto &idx : articulation) {
            belong[idx] = ptr++;
        }
        vector<int> last(ptr, -1);  // 用于检查是否关节点和联通块已经连过边没
        tree = Graph<T>(ptr);
        for (int i = 0; i < bc.size(); i++) {
            for (auto &e : bc[i]) {
                for (auto &v : {e.from, e.to}) {
                    if (belong[v] >= (int)bc.size()) {
                        // v 是割点
                        if (exchange(last[belong[v]], i) != i) {
                            // 没和 i 连通块连过边
                            tree.add_edge(belong[v], i, e.cost);
                        }
                    } else {
                        belong[v] = i;
                    }
                }
            }
        }

        group.resize(ptr);
        for (int i = 0; i < g.size(); i++) {
            group[belong[i]].emplace_back(i);
        }
    }
};