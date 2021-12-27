#include "../base.hpp"

template<typename T1, typename T2>
pair<vector<T1>, vector<T2>> zip(const vector<pair<T1, T2>> &A) {
    int N = A.size();
    pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)};
    rep(i, N) {
        res.first[i] = A[i].first;
        res.second[i] = A[i].second;
    }
    return res;
}

template<typename T1, typename T2, typename T3>
tuple<vector<T1>, vector<T2>, vector<T3>> zip(const vector<tuple<T1, T2, T3>> &A) {
    int N = A.size();
    tuple<vector<T1>, vector<T2>, vector<T3>> res = {vector<T1>(N), vector<T2>(N), vector<T3>(N)};
    rep(i, N) {
        get<0>(res)[i] = get<0>(A[i]);
        get<1>(res)[i] = get<1>(A[i]);
        get<2>(res)[i] = get<2>(A[i]);
    }
    return res;
}
