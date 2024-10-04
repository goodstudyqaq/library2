#include <bits/stdc++.h>

/*
带权并查集
http://oj.daimayuan.top/course/15/problem/719
*/

using namespace std;

template <typename T>
struct WeightedUnionFind {
    vector<int> f;
    vector<T> ws;

    WeightedUnionFind() {}
    WeightedUnionFind(int sz) : f(sz), ws(sz) {
        iota(f.begin(), f.end(), 0);
    }

    int find(int k) {
        if (f[k] == k) return k;
        int par = find(f[k]);
        ws[k] += ws[f[k]];
        return f[k] = par;
    }

    T weight(int t) {
        find(t);
        return ws[t];
    }

    bool unite(int x, int y, T w) {
        int fx = find(x);
        int fy = find(y);

        if (fx == fy) {
            return false;
        }

        ws[fx] = -ws[x] + w + ws[y];
        f[fx] = fy;
        return true;
    }
};