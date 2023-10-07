/*
・きっちり自力AC！
・確率DP
・最初、曲が流れている途中にも遷移しようとしたりしてもたついたけど、
　次の曲を流し始める瞬間だけ状態に持つように遷移させればOK。
　答えに該当する時間を跨ぐような遷移が来たら答えに足す。
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
    ll N, X;
    cin >> N >> X;
    vector<ll> T(N);
    cin >> T;

    vector<mint> dp(X + 1);
    mint ans = 0;
    dp[0] = 1;
    rep(i, X + 1) {
        rep(j, N) {
            if (i + T[j] > X) {
                if (j == 0) {
                    ans += dp[i] / N;
                }
            } else {
                dp[i + T[j]] += dp[i] / N;
            }
        }
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
