
#include <bits/stdc++.h>

#include <algorithm>
#include <limits>
#include <type_traits>

#include "./base.hpp"
#include "./point.hpp"

// https://goodstudyqaq.notion.site/Convex-hull-trick-263c5c0415c48017bc01c34c3d8d0bc0
using namespace std;

namespace geometry {
template <typename T>
struct ConvexHullTrick {
    struct Line {
        T a, b, r;
        bool operator<(Line &l) { return pair(a, b) > pair(l.a, l.b); }
        bool operator<(T x) { return r < x; }
    };

    ConvexHullTrick() = default;
    ConvexHullTrick(vector<Line> &lines, bool is_min = true) : lines(lines), is_min(is_min) {
        int n = lines.size();
        if (!is_min) {
            for (int i = 0; i < n; i++) {
                lines[i].a *= -1;
                lines[i].b *= -1;
            }
        }
        if (!ranges::is_sorted(lines, less())) {
            ranges::sort(lines, less());
        }

        // 求上凸包
        const T inf = numeric_limits<T>::max();
        vector<int> stk;
        stk.push_back(0);
        lines[stk.back()].r = inf;
        for (int i = 1; i < n; i++) {
            for (; !stk.empty(); stk.pop_back()) {
                if (lines[stk.back()].a == lines[i].a) {
                    continue;
                }
                // https://noshi91.hatenablog.com/entry/2021/03/23/200810
                T da = lines[stk.back()].a - lines[i].a;
                T db = lines[i].b - lines[stk.back()].b;
                lines[stk.back()].r = db / da - ((db < 0) & ((db % da) != 0));
                if (stk.size() == 1 || lines[stk.back()].r > lines[stk[stk.size() - 2]].r) break;
            }
            stk.push_back(i);
            lines[i].r = inf;
        }

        for (auto it : stk) {
            convex.emplace_back(lines[it]);
        }
    }
    T query(T x) {
        assert(!convex.empty());
        auto idx = lower_bound(convex.begin(), convex.end(), x) - convex.begin();
        return get_y(idx, x);
    }

   private:
    bool is_min;
    vector<Line> convex, lines;

    T get_y(int idx, T x) {
        return convex[idx].a * x + convex[idx].b;
    }
};

}  // namespace geometry
