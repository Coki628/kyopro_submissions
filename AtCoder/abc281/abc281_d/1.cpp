/*
・終了後自力AC…。
・modの状態を持って部分和DP
・0を倍数と考慮できておらず、時間内にWAが取れず通せなかった。
・あと終わってからTL見てて分かったけど、値として持つの、
　何倍になったかじゃなくて、普通に最大値を陽に持っててよかったね。。
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
    ll N, K, D;
    cin >> N >> K >> D;
    vector<ll> A(N);
    cin >> A;

    auto dp = listnd(N + 1, K + 1, D, -INF);
    dp[0][0][0] = 0;
    rep(i, N) {
        rep(j, K + 1) {
            rep(k, D) {
                if (dp[i][j][k] == -INF)
                    continue;
                auto [d, m] = divmod(k + A[i], D);
                chmax(dp[i + 1][j][k], dp[i][j][k]);
                if (j + 1 <= K) {
                    chmax(dp[i + 1][j + 1][m], dp[i][j][k] + d);
                }
            }
        }
    }
    ll ans = -1;
    if (dp[N][K][0] >= 0) {
        ans = D * dp[N][K][0];
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
