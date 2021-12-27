#include "../base.hpp"
#include "chmin.hpp"

template<typename T> T min(const vector<T> &A) {
    return *min_element(ALL(A));
}

template<typename key, typename val> val min(const map<key, val> &mp) {
    val res = numeric_limits<val>::max();
    for (auto& [k, v] : mp) chmin(res, v);
    return res;
}
