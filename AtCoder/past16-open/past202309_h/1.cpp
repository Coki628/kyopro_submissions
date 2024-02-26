/*
・きっちり自力AC！
・2日連続が不可という条件があるので、直前のやったやらないだけ持って2乗のDPやる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);

    auto dp = listnd(N + 1, M + 1, 2, -INF);
    dp[0][0][0] = 0;
    rep(i, N) {
        rep(j, M + 1) {
            rep(k, 2) {
                chmax(dp[i + 1][j][0], dp[i][j][k] + A[i]);
                if (k == 0 and j + 1 <= M) {
                    chmax(dp[i + 1][j + 1][1], dp[i][j][k]);
                }
            }
        }
    }
    ll ans = max(dp[N][M]);
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
