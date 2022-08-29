/*
・きっちり自力AC！
・dp[x][i] := 時間iまで見て位置xにいる時の最大値、をやる。
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
    ll N;
    cin >> N;
    ll M = 100000;
    auto A = listnd(5, M+1, 0LL);
    rep(i, N) {
        ll t, x, a;
        cin >> t >> x >> a;
        A[x][t] = a;
    }

    auto dp = listnd(5, M+1, -INF);
    dp[0][0] = 0;
    rep(i, M) {
        rep(x, 5) {
            if (x > 0) {
                chmax(dp[x-1][i+1], dp[x][i]+A[x-1][i+1]);
            }
            chmax(dp[x][i+1], dp[x][i]+A[x][i+1]);
            if (x < 4) {
                chmax(dp[x+1][i+1], dp[x][i]+A[x+1][i+1]);
            }
        }
    }
    ll ans = -INF;
    rep(x, 5) {
        chmax(ans, dp[x][M]);
    }
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
