#include "../macros.hpp"

// スターリング数(玉区別あり、箱区別なし、1個以上)
template<typename T>
vector<vector<T>> stirling(int N, int K) {
    auto dp = list2d<T>(N+1, K+1, 0);
    dp[0][0] = 1;
    rep(i, 1, N+1) {
        rep(k, 1, K+1) {
            dp[i][k] = dp[i-1][k-1] + dp[i-1][k]*k;
        }
    }
    return dp;
}
