// http://oj.daimayuan.top/course/15/problem/637 二维树状数组模板题
#include <bits/stdc++.h>
using namespace std;
// 多维动态大小数组，可以用于DP等场景。
template <typename T, int dimensions>
class md_vector;

template <int dimensions>
int md_size(const array<int, dimensions>& dsize) {
    int base = 1;
    for (int i = 0; i < dimensions; i++) {
        base *= dsize[i];
    }
    return base;
}

template <typename T, int dimensions, int idx_dimensions>
class md_vector_index {
   public:
    md_vector_index(md_vector<T, dimensions>& vec, int base = 0) : vector_(vec), base_(base) {
    }

    auto operator[](int v) {
        assert(v < vector_.dsize_[idx_dimensions - 1]);
        return md_vector_index<T, dimensions, idx_dimensions + 1>(vector_, (base_ + v) * vector_.dsize_[idx_dimensions]);
    }

   private:
    md_vector<T, dimensions>& vector_;
    int base_;
};

template <typename T, int dimensions>
class md_vector_index<T, dimensions, dimensions> {
   public:
    md_vector_index(md_vector<T, dimensions>& vec, int base = 0) : vector_(vec), base_(base) {
    }

    T& operator[](int v) {
        return vector_.data_[base_ + v];
    }

    md_vector<T, dimensions>& vector_;
    int base_;
};

template <typename T, int dimensions>
class md_vector {
   public:
    md_vector() {}
    md_vector(const md_vector<T, dimensions>& other) : data_(other.data_), dsize_(other.dsize_) {
    }

    md_vector(array<int, dimensions> dsize, T default_value = T())
        : dsize_(dsize), data_(md_size<dimensions>(dsize), default_value) {
    }

    md_vector& operator=(const md_vector<T, dimensions>& other) {
        data_ = other.data_;
        dsize_ = other.dsize_;
        return *this;
    }

    auto operator[](int v) {
        return md_vector_index<T, dimensions, 1>(*this)[v];
    }

    T& operator[](array<int, dimensions> idx) {
        int base = 0;
        for (int i = 0; i < dimensions; i++) {
            base *= dsize_[i];
            base += idx[i];
        }
        return data_[base];
    }

    vector<T> data_;
    array<int, dimensions> dsize_;
};

template <typename T, int dimensions>
istream& operator>>(istream& in, md_vector<T, dimensions>& vec) {
    return in >> vec.data_;
}

template <typename T, int dimensions>
void make_md_presum(md_vector<T, dimensions>& vec) {
    int diff = 1, base = 0;
    for (int currD = dimensions - 1; currD >= 0; currD--) {
        base = diff * vec.dsize_[currD];
        for (int i = 0; i + diff < vec.data_.size(); i++) {
            if (i % base + diff < base) {
                vec.data_[i + diff] += vec.data_[i];
            }
        }
        diff = base;
    }
}

template <typename T, int dimensions, int idx_dimensions>
string to_string(md_vector_index<T, dimensions, idx_dimensions>& vec) {
    int sz = vec.vector_.dsize_[idx_dimensions - 1];
    string s = "{";
    for (int i = 0; i < sz; i++) {
        s += to_string(vec[i]);
        if (i != sz - 1) {
            s += ", ";
        }
    }
    s += "}";
    return s;
}

template <typename T, int dimensions>
string to_string(md_vector<T, dimensions>& vec) {
    int sz = vec.dsize_[0];
    string s = "{";
    for (int i = 0; i < sz; i++) {
        auto it = vec[i];
        s += to_string(it);
        if (i != sz - 1) {
            s += ", ";
        }
    }
    s += "}";
    return s;
}
