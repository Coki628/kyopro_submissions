/*
・過去と違う方針が生えたので実装してみた。これでも問題なく通った。
・最後に時間0で取れる分は、途中で取るとみなしても、他を時間T未満で取れれば問題ない。
　時間0で取れる分を使ったかどうかを状態に持ってナップザックする。
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
    ll N, T;
    cin >> N >> T;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    ll dp[N + 1][T][2] = {};
    rep(i, N + 1) {
        rep(j, T) {
            rep(k, 2) {
                dp[i][j][k] = -INF;
            }
        }
    }
    dp[0][0][0] = 0;
    rep(i, N) {
        rep(j, T) {
            rep(k, 2) {
                if (dp[i][j][k] == -INF) continue;
                chmax(dp[i + 1][j][k], dp[i][j][k]);
                if (j + A[i] < T) {
                    chmax(dp[i + 1][j + A[i]][k], dp[i][j][k] + B[i]);
                }
                if (k == 0) {
                    chmax(dp[i + 1][j][1], dp[i][j][k] + B[i]);
                }
            }
        }
    }
    ll ans = -INF;
    rep(j, T) {
        chmax(ans, dp[N][j][1]);
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
