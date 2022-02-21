/*
・さすがにこれは速攻自力AC。
・DPする。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, X;
    cin >> N >> X;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    auto dp = list2d(N+1, X+1, false);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, X+1) {
            if (!dp[i][j]) continue;
            if (j+A[i] <= X) {
                dp[i+1][j+A[i]] = true;
            }
            if (j+B[i] <= X) {
                dp[i+1][j+B[i]] = true;
            }
        }
    }
    if (dp[N][X]) Yes();
    else No();
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
