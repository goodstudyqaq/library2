#include "fast-fourier-transform.hpp"

/*
 * @brief Arbitrary Mod Convolution(任意mod畳み込み)
 */
template <typename T>
struct ArbitraryModConvolution {
  using real = FastFourierTransform::real;
  using C = FastFourierTransform::C;

  ArbitraryModConvolution() = default;

  static vector<T> multiply(const vector<T> &a, const vector<T> &b,
                            int need = -1) {
    if (need == -1) need = a.size() + b.size() - 1;
    int nbase = 0;
    while ((1 << nbase) < need) nbase++;
    FastFourierTransform::ensure_base(nbase);
    int sz = 1 << nbase;
    vector<C> fa(sz);
    for (int i = 0; i < a.size(); i++) {
      fa[i] = C(int64_t(a[i]) & ((1 << 15) - 1), int64_t(a[i]) >> 15);
    }
    fft(fa, sz);
    vector<C> fb(sz);
    if (a == b) {
      fb = fa;
    } else {
      for (int i = 0; i < b.size(); i++) {
        fb[i] = C(int64_t(b[i]) & ((1 << 15) - 1), int64_t(b[i]) >> 15);
      }
      fft(fb, sz);
    }
    real ratio = 0.25 / sz;
    C r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
    for (int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      C a1 = (fa[i] + fa[j].conj());
      C a2 = (fa[i] - fa[j].conj()) * r2;
      C b1 = (fb[i] + fb[j].conj()) * r3;
      C b2 = (fb[i] - fb[j].conj()) * r4;
      if (i != j) {
        C c1 = (fa[j] + fa[i].conj());
        C c2 = (fa[j] - fa[i].conj()) * r2;
        C d1 = (fb[j] + fb[i].conj()) * r3;
        C d2 = (fb[j] - fb[i].conj()) * r4;
        fa[i] = c1 * d1 + c2 * d2 * r5;
        fb[i] = c1 * d2 + c2 * d1;
      }
      fa[j] = a1 * b1 + a2 * b2 * r5;
      fb[j] = a1 * b2 + a2 * b1;
    }
    fft(fa, sz);
    fft(fb, sz);
    vector<T> ret(need);
    for (int i = 0; i < need; i++) {
      int64_t aa = llround(fa[i].x);
      int64_t bb = llround(fb[i].x);
      int64_t cc = llround(fa[i].y);
      aa = int64_t(T(aa)), bb = int64_t(T(bb)), cc = int64_t(T(cc));
      ret[i] = aa + (bb << 15) + (cc << 30);
    }
    return ret;
  }
};
