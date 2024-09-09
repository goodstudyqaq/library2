#include <bits/stdc++.h>

#include <algorithm>
#include <functional>
using namespace std;

// https://codeforces.com/contest/2004/problem/G

template <typename T>
struct MinQueue {
    vector<pair<T, T>> st1, st2;
    // 注意顺序
    function<T(T&, T&)> f;

    MinQueue(function<T(T&, T&)> &f) : f(f) {}

    void push(T &a) {
        if (!st1.empty()) {
            st1.push_back({a, f(st1.back().second, a)});
        } else {
            st1.push_back({a, a});
        }
    }

    void pop() {
        if (st2.empty()) {
            st2 = st1;
            reverse(st2.begin(), st2.end());
            st1.clear();

            st2[0].second = st2[0].first;
            for (int i = 1; i < st2.size(); i++) {
                st2[i].second = f(st2[i].first, st2[i - 1].second);
            }
        }
        st2.pop_back();
    }

    T get() {
        if (st1.empty()) {
            return st2.back().second;
        }
        if (st2.empty()) {
            return st1.back().second;
        }

        T res = f(st2.back().second, st1.back().second);
        return res;
    }
};