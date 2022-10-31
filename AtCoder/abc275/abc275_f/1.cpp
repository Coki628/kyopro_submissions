/*
・きっちり自力AC！
・部分和DP
・制約的に愚直に2乗DPでOK。直前を使ったかどうかを状態に持って、
　連続使用を区切る時にコスト+1する。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    cin >> A;

    auto dp = listnd(2, N+1, M+1, INF);
    dp[1][0][0] = 0;
    rep(i, N) {
        rep(j, M+1) {
            chmin(dp[0][i+1][j], dp[0][i][j]);
            chmin(dp[0][i+1][j], dp[1][i][j] + 1);
            if (j+A[i] <= M) {
                chmin(dp[1][i+1][j+A[i]], dp[0][i][j]);
                chmin(dp[1][i+1][j+A[i]], dp[1][i][j]);
            }
        }
    }
    rep(i, 1, M+1) {
        ll res = min(dp[0][N][i], dp[1][N][i]);
        if (res == INF) {
            res = -1;
        }
        print(res);
    }
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
