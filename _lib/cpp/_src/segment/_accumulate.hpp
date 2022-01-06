#include "../macros.hpp"

template<typename T>
vector<T> accumulate(vector<T> &A, bool indexed=0) {
    int n = A.size();
    auto res = A;
    rep(i, n-1) res[i+1] += res[i];
    if (indexed) res.insert(res.begin(), 0);
    return res;
}
