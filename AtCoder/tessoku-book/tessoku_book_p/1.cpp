/*
・DP基本(1次元)
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
    ll N;
    cin >> N;
    vector<ll> A(N + 1), B(N + 1);
    rep(i, 2, N + 1) {
        cin >> A[i];
    }
    rep(i, 3, N + 1) {
        cin >> B[i];
    }

    vector<ll> dp(N + 1, INF);
    dp[1] = 0;
    rep(i, 2, N + 1) {
        chmin(dp[i], dp[i - 1] + A[i]);
        chmin(dp[i], dp[i - 2] + B[i]);
    }
    print(dp[N]);
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
