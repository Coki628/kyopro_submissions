/*
・編集距離DP
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    string S, T;
    cin >> S >> T;
    ll N = S.size(), M = T.size();

    // SをTに一致させる
    auto dp = listnd(N + 1, M + 1, INF);
    dp[0][0] = 0;
    rep(i, N + 1) {
        rep(j, M + 1) {
            // 削除
            if (i + 1 <= N) {
                chmin(dp[i + 1][j], dp[i][j] + 1);
            }
            // 挿入
            if (j + 1 <= M) {
                chmin(dp[i][j + 1], dp[i][j] + 1);
            }
            // 変更
            if (i + 1 <= N and j + 1 <= M) {
                chmin(dp[i + 1][j + 1], dp[i][j] + (S[i] != T[j]));
            }
        }
    }
    print(dp[N][M]);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
