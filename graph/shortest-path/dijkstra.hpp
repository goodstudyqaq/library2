#include "../graph-template.hpp"

template <typename T, typename T2 = long long>
struct ShortestPath {
    vector<T> dist;
    vector<int> from, to;
    vector<T2> num;
    T inf;
};

template <typename T, typename T2 = long long>
ShortestPath<T, T2> dijkstra(const Graph<T> &g, int s) {
    // O(mlogn)
    const auto inf = numeric_limits<T>::max();
    vector<T> dist(g.size(), inf);
    vector<int> from(g.size(), -1), id(g.size(), -1);
    vector<T2> cnt(g.size());

    using Pi = pair<T, int>;
    priority_queue<Pi, vector<Pi>, greater<> > Q;
    dist[s] = 0;
    cnt[s] = 1;
    Q.emplace(dist[s], s);
    while (!Q.empty()) {
        T cost;
        int u;
        tie(cost, u) = Q.top();
        Q.pop();
        if (dist[u] < cost) {  // 没有用 vis
            continue;
        }
        for (auto &v : g[u]) {
            auto w = cost + v.cost;
            if (dist[v.to] > w) {
                cnt[v.to] = cnt[u];
                dist[v.to] = w;
                from[v.to] = u;
                id[v.to] = v.idx;
                Q.emplace(dist[v.to], v.to);
            } else if (dist[v.to] == w) {
                cnt[v.to] += cnt[w];
            }
        }
    }
    return {dist, from, id, cnt, inf};
}

template <typename T, typename T2 = long long>
ShortestPath<T, T2> normal_dijkstra(const Graph<T> &g, int s) {
    // O(n^2)
    int n = g.size();
    const auto inf = numeric_limits<T>::max();
    vector<T> dist(g.size(), inf);
    vector<int> from(g.size(), -1), id(g.size(), -1);
    vector<bool> vis(n);
    vector<T2> cnt(g.size());
    dist[s] = 0;
    cnt[s] = 1;
    for (int i = 0; i < n; i++) {
        int x;
        T m = inf;
        for (int y = 0; y < n; y++) {
            if (!vis[y] && dist[y] <= m) {
                m = dist[x = y];
            }
        }
        vis[x] = 1;
        for (auto &e : g[x]) {
            auto w = dist[x] + e.cost;
            if (dist[e.to] > w) {
                dist[e.to] = w;
                from[e.to] = x;
                id[e.to] = e.idx;
                cnt[e.to] = cnt[x];
            } else if (dist[e.to] == w) {
                cnt[e.to] += cnt[x];
            }
        }
    }
    return {dist, from, id, cnt, inf};
}
