/*
・部分和DP
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
    ll N, S;
    cin >> N >> S;
    vector<ll> A(N);
    cin >> A;

    auto dp = listnd(N + 1, S + 1, 0);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, S + 1) {
            dp[i + 1][j] |= dp[i][j];
            if (j + A[i] <= S) {
                dp[i + 1][j + A[i]] |= dp[i][j];
            }
        }
    }
    if (dp[N][S]) {
        Yes();
    } else {
        No();
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
