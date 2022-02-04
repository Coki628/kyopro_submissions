#include "../macros.hpp"
#include "../common/listnd.hpp"

// nCr列挙 (計算量：O(n*r))
template<typename T>
vector<vector<T>> nCr(int n, int r) {
    auto dp = list2d(n+1, r+1, (T)0);
    dp[0][0] = 1;
    rep(i, 1, n+1) {
        dp[i][0] = 1;
        rep(j, 1, r+1) {
            dp[i][j] = dp[i-1][j-1]+dp[i-1][j];
        }
    }
    return dp;
}

// nCr (計算量：O(r))
template<typename T>
T nCr(int n, int r) {
    T res = 1;
    rep(i, r) res = res*(T)(n-i)/(T)(i+1);
    return res;
}
