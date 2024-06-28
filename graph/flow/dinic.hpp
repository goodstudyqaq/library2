#include <bits/stdc++.h>

#include <limits>
using namespace std;

/*
Dinic 最大流
*/

template <typename flow_t>
struct Dinic {
    const flow_t INF;

    struct edge {
        int to;
        flow_t cap;
        int rev;
        bool is_rev;
        int idx;
    };

    vector<vector<edge>> graph;
    vector<int> min_cost, iter;

    explicit Dinic(int V) : INF(numeric_limits<flow_t>::max()), graph(V) {}

    void add_edge(int from, int to, flow_t cap, int idx = -1) {
        graph[from].emplace_back(edge{to, cap, (int)graph[to].size(), false, idx});
        graph[to].emplace_back(edge{from, 0, (int)graph[from].size(), true, idx});
    }

    bool build_augment_path(int s, int t) {
        min_cost.assign(graph.size(), -1);
        queue<int> Q;
        Q.push(s);
        min_cost[s] = 0;
        while (!Q.empty() && min_cost[t] == -1) {
            int u = Q.front();
            Q.pop();
            for (auto &e : graph[u]) {
                if (e.cap > 0 && min_cost[e.to] == -1) {
                    min_cost[e.to] = min_cost[u] + 1;
                    Q.push(e.to);
                }
            }
        }
        return min_cost[t] != -1;
    }

    flow_t find_min_dist_augment_path(int idx, const int t, flow_t flow) {
        if (idx == t) return flow;
        for (int &i = iter[idx]; i < (int)graph[idx].size(); i++) {
            edge &e = graph[idx][i];
            if (e.cap > 0 && min_cost[idx] < min_cost[e.to]) {
                flow_t d = find_min_dist_augment_path(e.to, t, min(flow, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    flow_t max_flow(int s, int t) {
        flow_t flow = 0;
        while (build_augment_path(s, t)) {
            iter.assign(graph.size(), 0);
            flow_t f;
            while ((f = find_min_dist_augment_path(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }

    vector<bool> min_cut(int s) {
        vector<bool> used(graph.size());
        queue<int> Q;
        Q.push(s);
        used[s] = true;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto &e : graph[u]) {
                if (e.cap > 0 && !used[e.to]) {
                    used[e.to] = 1;
                    Q.push(e.to);
                }
            }
        }
        return used;
    }
};