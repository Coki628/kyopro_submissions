#include "../macros.hpp"

template<typename T, typename F>
vector<T> mapping(const vector<string> &A, const F &f) {
    int N = A.size();
    vector<T> res(N);
    rep(i, N) res[i] = f(A[i]);
    return res;
}
