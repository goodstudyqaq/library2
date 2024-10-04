#include <bits/stdc++.h>
using namespace std;
/*
http://oj.daimayuan.top/course/15/problem/717
笛卡尔树：https://oi-wiki.org/ds/cartesian-tree/
一个排列，拿最小的做根，然后将排列分成左右两边，然后继续递归这个操作得到的树
 */

template <typename T>
vector<int> cartesian_tree(const vector<T> &v) {
    int n = (int)v.size();
    vector<int> par(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        int last = -1;
        while (!st.empty() && v[st.top()] >= v[i]) {
            last = st.top();
            st.pop();
        }
        if (!st.empty()) par[i] = st.top();
        if (last >= 0) par[last] = i;
        st.emplace(i);
    }
    return par;
}