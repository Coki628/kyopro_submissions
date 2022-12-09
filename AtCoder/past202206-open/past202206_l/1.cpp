/*
・LCSのDP
・ほぼLCSのDP。Kが小さいので、k回操作してみたいな添字を足せばOK。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    string S, T;
    ll K;
    cin >> S >> T >> K;
    ll N = S.size();
    ll M = T.size();

    auto dp = listnd(N + 1, M + 1, K + 1, -INF);
    dp[0][0][0] = 0;
    rep(i, N + 1) {
        rep(j, M + 1) {
            rep(k, K + 1) {
                if (i < N) {
                    chmax(dp[i + 1][j][k], dp[i][j][k]);
                }
                if (j < M) {
                    chmax(dp[i][j + 1][k], dp[i][j][k]);
                }
                if (i < N and j < M) {
                    if (S[i] == T[j]) {
                        chmax(dp[i + 1][j + 1][k], dp[i][j][k] + 1);
                    }
                    if (k < K) {
                        chmax(dp[i + 1][j + 1][k + 1], dp[i][j][k] + 1);
                    }
                }
            }
        }
    }
    ll ans = max(dp[N][M]);
    print(ans);
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
