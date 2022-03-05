/*
・さすがにさくっと自力AC！
・易しい桁DP系
・直前の桁の状態を持ってDP。こういうしっかりDPな感じがCでもう出るんだねぇ、、ってなるね。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;

    auto dp = list2d<mint>(N+1, 10, 0);
    rep(i, 1, 10) {
        dp[1][i] = 1;
    }
    rep(i, 1, N) {
        rep(j, 1, 10) {
            rep(k, 1, 10) {
                if (abs(j-k) <= 1) {
                    dp[i+1][k] += dp[i][j];
                }
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
