/*
・どう考えてもこの序盤で確率DPはおかしいんだけど、
　考察するよりこのくらいなら手動かす方が早そうだったので書いた。
・公式解は3重ループで出目を全探索だった。まあそうだよね…。
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
    ll N = 3, M = 6;
    auto P = listnd(N, M, 0LL);
    rep(i, N) {
        cin >> P[i];
    }

    ll K = 18;
    auto dp = listnd(N + 1, K + 1, (ld)0);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, K + 1) {
            rep(k, M) {
                if (j + k + 1 > K) continue;
                dp[i + 1][j + k + 1] += dp[i][j] * P[i][k] / 100;
            }
        }
    }
    rep(k, 1, K + 1) {
        print(dp[N][k]);
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
