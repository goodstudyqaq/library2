#include <bits/stdc++.h>
using namespace std;

/*
struct Structure {
    vector<Data> datas;
    virtual void add(const Data &d) {
        datas.emplace_back(d);
    }
    void build() {
    }
    static Structure merge(const Structure &s1, const Structure &s2) {
        Structure new_s;
        for (auto &d : s1.datas) {
            new_s.add(d);
        }
        for (auto &d : s2.datas) {
            new_s.add(d);
        }
        new_s.build();
        return new_s;
    }


    size_t size() const { return datas.size(); }
};
*/

template <typename Structure, typename Data>
struct BinaryGrouping {
    vector<Structure> structures;
    const function<Structure(const Structure &, const Structure &)> merge;
    BinaryGrouping() : merge(Structure::merge) {}

    void insert(const Data &d) {
        Structure s;
        s.add(d);
        s.build();

        structures.emplace_back(s);

        while (structures.size() >= 2 && structures[structures.size() - 1].size() == structures[structures.size() - 2].size()) {
            Structure new_s = merge(structures[structures.size() - 1], structures[structures.size() - 2]);
            structures.pop_back();
            structures.pop_back();
            structures.emplace_back(new_s);
        }
    }
};
