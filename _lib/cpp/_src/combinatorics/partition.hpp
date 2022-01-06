#include "../macros.hpp"
#include "../common/listnd.hpp"

// 分割数(玉区別なし、箱区別なし、制限なし) ※未Verify
ll partition(int N, int K) {
    // dp[i][j] := jのi分割の総数
    auto dp = list2d(K+1, N+1, 0LL);
    dp[0][0] = 1;
    rep(i, 1, K+1) {
        rep(j, N+1) {
            dp[i][j] += dp[i-1][j];
            if (j - i >= 0) {
                dp[i][j] += dp[i][j-i];
            }
            dp[i][j] %= MOD;
        }
    }
    return dp[K][N];
}
