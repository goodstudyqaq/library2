#pragma once
#include <bits/stdc++.h>

#include <cstddef>
using namespace std;

struct UnionFind {
    vector<int> data;

    UnionFind() = default;

    explicit UnionFind(size_t sz) : data(sz, -1) {}

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }
    int find(int x) {
        if (data[x] < 0) return x;
        return data[x] = find(data[x]);
    }
    int size(int x) {
        return -data[find(x)];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    vector<vector<int>> groups() {
        int n = (int)data.size();
        vector<vector<int>> ans;
        for (int i = 0; i < n; i++) {
            ans[find(i)].push_back(i);
        }
        ans.erase(remove_if(ans.begin(), ans.end(), [&](const vector<int>& v) {
            return v.empty();
        }));
        return ans;
    }
};