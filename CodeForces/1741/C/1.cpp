/*
・自力AC！
・累積和で前計算、DP
・dp[i][j] := i番目まで見て和がjの時のthickness(和の状態は1回決まると固定なので状態数爆発しない)
　ってDPしたけど、もっと簡単にできそう。
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
    auto A = LIST(N);

    Accumulate<ll> acc(A);
    vector<defaultdict<ll, ll>> dp(N+1, {INF});
    dp[0][0] = 0;
    rep(i, N) {
        for (auto [k, v] : dp[i]) {
            if (i == 0) {
                rep(j, 1, N+1) {
                    dp[j][acc.query(i, j)] = j-i;
                }
            } else {
                rep(j, i+1, N+1) {
                    if (acc.query(i, j) != k) continue;
                    chmin(dp[j][k], max(v, j-i));
                }
            }
        }
    }
    ll ans = INF;
    for (auto [k, v] : dp[N]) {
        chmin(ans, v);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
