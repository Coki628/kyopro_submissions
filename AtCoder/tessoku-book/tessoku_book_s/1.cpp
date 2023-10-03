/*
・ナップザック
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
    ll N, W;
    cin >> N >> W;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    auto dp = listnd(N + 1, W + 1, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, W + 1) {
            chmax(dp[i + 1][j], dp[i][j]);
            if (j + A[i] <= W) {
                chmax(dp[i + 1][j + A[i]], dp[i][j] + B[i]);
            }
        }
    }
    ll ans = max(dp[N]);
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
