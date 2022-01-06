#pragma once
#include "../macros.hpp"
#include "../common/listnd.hpp"

// 行列の積
template<typename T>
vector<vector<T>> mat_dot(const vector<vector<T>> &A, const vector<vector<T>> &B) {
    int n1 = A.size();
    int n2 = A[0].size();
    int m2 = B[0].size();
    auto res = list2d(n1, m2, (T)0);
    rep(i, n1) {
        rep(k, n2) {
            if (A[i][k] == 0) continue;
            rep(j, m2) {
                res[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return res;
}
