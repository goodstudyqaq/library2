#include <bits/stdc++.h>

#include "./base.hpp"
using namespace std;

namespace geometry {
template <typename T>
struct TPoint {
    T x, y;
    int id;
    TPoint() : x(0), y(0), id(-1) {}
    TPoint(const T& x_, const T& y_) : x(x_), y(y_), id(-1) {}
    TPoint(const T& x_, const T& y_, int id_) : x(x_), y(y_), id(id_) {}

    static constexpr T eps = static_cast<T>(1e-9);

    inline TPoint operator+(const TPoint& rhs) const { return TPoint(x + rhs.x, y + rhs.y); }
    inline TPoint operator-(const TPoint& rhs) const { return TPoint(x - rhs.x, y - rhs.y); }
    inline TPoint operator*(const T& rhs) const { return TPoint(x * rhs, y * rhs); }
    inline TPoint operator/(const T& rhs) const { return TPoint(x / rhs, y / rhs); }

    friend T smul(const TPoint& a, const TPoint& b) {
        // 点积
        return a.x * b.x + a.y * b.y;
    }

    friend T vmul(const TPoint& a, const TPoint& b) {
        // 叉积
        return a.x * b.y - a.y * b.x;
    }

    inline T abs2() const {
        return x * x + y * y;
    }

    inline bool operator<(const TPoint& rhs) const {
        return (y < rhs.y || (y == rhs.y && x < rhs.x));
    }
};

using Point = TPoint<long long>;
template <typename T>
string to_string(const TPoint<T>& p) {
    return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}

template <typename T>
bool check(const TPoint<T>& a, const TPoint<T>& b, const TPoint<T>& c, bool boundaryContain) {
    // ab * bc >= 0 判断 bc 是不是在 ab 的左侧
    // return (b.F-a.F)*(c.S-b.S) >= (b.S-a.S)*(c.F-b.F); return ab * bc >= 0

    auto check2 = [&](T x, T y) {
        // 包含边界上的点，那么不用加等于号
        return boundaryContain ? (x > y) : (x >= y);
    };

    if (b.x == a.x || c.x == b.x) {
        return check2(sign(b.x - a.x) * sign(c.y - b.y), sign(c.x - b.x) * sign(b.y - a.y));
    }
    // return (b.second - a.second) / (a.first - b.first) >= (c.second - b.second) / (b.first - c.first);

    auto ab = b - a;
    auto bc = c - b;

    if (sign(ab.x) * sign(bc.y) != sign(ab.y) * sign(bc.x)) {
        return sign(ab.x) * sign(bc.y) >= sign(ab.y) * sign(bc.x);
    }

    TPoint<T> left = {bc.y / bc.x, bc.y % bc.x};
    TPoint<T> right = {ab.y / ab.x, ab.y % ab.x};

    if (left.x != right.x) {
        return left.x > right.x;
    }

    return check2(left.y * ab.x, right.y * bc.x);
    // auto ab = b - a;
    // auto bc = c - b;
    // // 有可能会爆 long long, 有时候需要用除法来避免溢出
    // return vmul(ab, bc) >= 0;
}

}  // namespace geometry
