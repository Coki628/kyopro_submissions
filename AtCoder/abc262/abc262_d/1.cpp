/*
・きっちり自力AC！これは早かった。
・平均が整数→和が取った個数で割り切れる、なので最終的に取る個数を全探索。3乗DPをN回やる。
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
    auto A = LIST(N);

    mint ans = 0;
    rep(mod, 1, N+1) {
        auto dp = list3d(N+1, mod+1, mod, (mint)0);
        dp[0][0][0] = 1;
        rep(i, N) {
            rep(j, mod+1) {
                rep(k, mod) {
                    if (dp[i][j][k] == 0) continue;
                    dp[i+1][j][k] += dp[i][j][k];
                    if (j+1 <= mod) dp[i+1][j+1][(k+A[i])%mod] += dp[i][j][k];
                }
            }
        }
        rep(k, mod) {
            if (k%mod == 0) {
                ans += dp[N][mod][k];
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
