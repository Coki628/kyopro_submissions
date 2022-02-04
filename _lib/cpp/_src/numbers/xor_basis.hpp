#include "base.hpp"
#include "../common/chmin.hpp"

// XOR基底
template<typename T>
vector<T> get_xor_basis(const vector<T> &A) {
    vector<T> basis;
    for (auto a : A) {
        for (auto b : basis) {
            chmin(a, a^b);
        }
        if (a > 0) basis.eb(a);
    }
    return basis;
}
