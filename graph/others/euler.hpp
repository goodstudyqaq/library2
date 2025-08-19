#pragma once
#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to;
    bool exists;
    int revref;

    bool operator<(const edge& b) const { return to < b.to; }
};

const int maxn = 2e3 + 5;
vector<edge> beg[maxn];
int cnt[maxn];

vector<int> ans;

void Hierholzer(int x, int d) {  // 关键函数
    for (int& i = cnt[x]; i < (int)beg[x].size();) {
        if (beg[x][i].exists) {
            edge e = beg[x][i];
            beg[x][i].exists = 0;
            beg[e.to][e.revref].exists = 0;
            ++i;
            Hierholzer(e.to, d + 1);
        } else {
            ++i;
        }
    }
    ans.push_back(x);
}

void add_edge(int u, int v) {
    int sz1 = beg[u].size();
    int sz2 = beg[v].size();
    if (u != v) {
        beg[u].push_back(edge{v, 1, sz2});
        beg[v].push_back(edge{u, 1, sz1});
    } else {
        // 自环
        beg[u].push_back(edge{v, 1, sz2});
    }
}
