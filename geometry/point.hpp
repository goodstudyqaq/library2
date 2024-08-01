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

template <typename T>
string to_string(const TPoint<T>& p) {
    return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}

template <typename T>
bool compare_by_polar_angle(const TPoint<T>& a, const TPoint<T>& b) {
    T x = vmul(a, b);
    return x == 0 ? (a.abs2() < b.abs2()) : x > 0;
}

}  // namespace geometry
