#include <bits/stdc++.h>
using namespace std;
namespace geometry {
template <typename T>
const constexpr T EPS = static_cast<T>(1e-8);
template <typename T>
const constexpr T PI = acos(static_cast<T>(-1));

template <typename T>
inline int sign(const T &r) {
    return r < -EPS<T> ? -1 : r > EPS<T> ? 1
                                         : 0;
}

template <typename T>
inline bool equals(const T &a, const T &b) { return sign(a - b) == 0; }

}  // namespace geometry