#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"
#include "../graph/shortest-path/dijkstra.hpp"

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    Graph<int> g(n);
    g.read(m, 0, true, true);
    auto res = dijkstra(g, s);
    for (auto &dist : res.dist) {
        if (dist == res.inf) {
            cout << "INF" << endl;
        } else {
            cout << dist << endl;
        }
    }
}