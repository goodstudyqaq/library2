#include <bits/stdc++.h>

#include "../../structure/others/md-vector.hpp"

using namespace std;
template <typename T>
struct Matrix {
    md_vector<T, 2> A;

    Matrix() {}
    Matrix(int n, int m) : A({n, m}) {}
    Matrix(int n) : A({n, n}) {}

    int height() const {
        return A.dsize_[0];
    }

    int width() const {
        return A.dsize_[1];
    }

    inline auto operator[](int k) { return A[k]; }

    static Matrix I(int n) {
        Matrix<T> mat(n);
        for (int i = 0; i < n; i++) {
            mat[i][i] = 1;
        }
        return mat;
    }

    Matrix &operator+=(Matrix &b) {
        int n = height(), m = width();
        assert(n == b.height() && m == b.width());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] += b[i][j];
            }
        }
        return (*this);
    }

    Matrix &operator-=(Matrix &b) {
        int n = height(), m = width();
        assert(n == b.height() && m == b.width());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] -= b[i][j];
            }
        }
        return (*this);
    }

    Matrix &operator*=(Matrix &b) {
        int n = height(), m = b.width(), p = width();

        assert(p == b.height());

        Matrix<T> C(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < p; k++) {
                    C[i][j] += (*this)[i][k] * b[k][j];
                }
            }
        }
        swap(this->A, C.A);
        return (*this);
    }

    Matrix &operator^=(long long k) {
        Matrix<T> b = Matrix<T>::I(height());
        while (k) {
            if (k & 1) b *= *this;
            *this *= *this;
            k >>= 1LL;
        }
        swap(this->A, b.A);
        return (*this);
    }

    Matrix operator+(const Matrix &b) {
        return (Matrix(*this) += b);
    }

    Matrix operator-(const Matrix &b) {
        return (Matrix(*this) -= b);
    }
    Matrix operator*(const Matrix &b) {
        return (Matrix(*this) *= b);
    }
    Matrix operator^(const long long k) {
        return (Matrix(*this) ^= k);
    }

    T determinant() {
        // 行列式辗转相除法
        assert(this->height() == this->width());
        Matrix<T> B(*this);
        T res = 1;
        int n = this->height();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                while (B[j][i] != 0) {
                    T t = B[i][i] / B[j][i];
                    for (int k = i; k < n; k++) {
                        B[i][k] -= B[j][k] * t;
                        swap(B[i][k], B[j][k]);
                    }
                    res = -res;
                }
            }
            if (B[i][i] == 0) return 0;
            res *= B[i][i];
        }
        return res;
    }
};