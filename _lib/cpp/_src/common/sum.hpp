#include "../../template.hpp"

template<typename T> T sum(const vector<T> &A) {
    return accumulate(ALL(A), (T)0);
}

template<typename key, typename val> val sum(const map<key, val> &mp) {
    val res = 0;
    for (auto& [k, v] : mp) res += v;
    return res;
}
