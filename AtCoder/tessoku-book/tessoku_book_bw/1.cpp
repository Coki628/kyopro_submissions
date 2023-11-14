/*
・なんとか自力AC！
・ソートしてDP
・DP遷移をミスってるのに気付かずに相当時間を使ってしまった。
　WAが大量だったからそもそも怪しかったんだけど、気付けよーって感じ。。
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
    vector<pll> DT;
    rep(i, N) {
        ll t, d;
        cin >> t >> d;
        DT.eb(d, t);
    }

    ll M = 1440 * 2;
    sort(ALL(DT));
    auto dp = listnd(N + 1, M + 1, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        auto [d, t] = DT[i];
        rep(j, M + 1) {
            chmax(dp[i + 1][j], dp[i][j]);
            if (j + t <= d) {
                chmax(dp[i + 1][j + t], dp[i][j] + 1);
            }
        }
    }
    ll ans = 0;
    rep(j, M + 1) {
        chmax(ans, dp[N][j]);
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
