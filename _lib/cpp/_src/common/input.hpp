#include "../../template.hpp"

template<typename T=ll> vector<T> LIST(ll N) {
    vector<T> A(N);
    rep(i, N) {
        cin >> A[i];
    }
    return A;
}
