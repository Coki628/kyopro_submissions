/*
・きっちり自力AC！
・累積和で貰うDP高速化。K=0で区間が被る1WA…。
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
    ll N, M, K;
    cin >> N >> M >> K;

    auto dp = list2d(N+1, M+1, (mint)0);
    rep(j, 1, M+1) {
        dp[1][j] = 1;
    }
    rep(i, 2, N+1) {
        Accumulate<mint> acc(dp[i-1]);
        rep(j, 1, M+1) {
            dp[i][j] += acc.query(1, max(j-K+1, 1LL));
            dp[i][j] += acc.query(min(j+K, M+1), M+1);
            if (K == 0) {
                dp[i][j] -= dp[i-1][j];
            }
        }
    }
    mint ans = sum(dp[N]);
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
