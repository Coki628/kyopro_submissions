/*
・きっちり自力AC。
・5種類の状態全部持って6重ループでDPした。
　でも想定はビットの2値の代わりに5値持てるかな、みたいな話だったそう。
　あとこの形にするにしても、mapにvectorの状態持たせるやつ使うと
　もっと楽に書けたなー、ってTL見てて思った。mapでDP忘れてた。
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
    ll N, K, P;
    ll M = 5;
    cin >> N >> K >> P;
    vector<ll> C(N);
    auto A = listnd(N, M, INF);
    rep(i, N) {
        cin >> C[i];
        rep(j, K) {
            cin >> A[i][j];
        }
    }

    ll dp[N + 1][P + 1][P + 1][P + 1][P + 1][P + 1] = {};
    rep(i, N + 1) {
        rep(j, P + 1) {
            rep(k, P + 1) {
                rep(l, P + 1) {
                    rep(m, P + 1) {
                        rep(n, P + 1) {
                            dp[i][j][k][l][m][n] = INF;
                        }
                    }
                }
            }
        }
    }
    dp[0][0][0][0][0][0] = 0;
    rep(i, N) {
        rep(j, P + 1) {
            rep(k, P + 1) {
                rep(l, P + 1) {
                    rep(m, P + 1) {
                        rep(n, P + 1) {
                            chmin(dp[i + 1][j][k][l][m][n], dp[i][j][k][l][m][n]);
                            chmin(dp[i + 1][min(j + A[i][0], P)][min(k + A[i][1], P)][min(l + A[i][2], P)][min(m + A[i][3], P)][min(n + A[i][4], P)], dp[i][j][k][l][m][n] + C[i]);
                        }
                    }
                }
            }
        }
    }
    ll ans = dp[N][P][P][P][P][P] < INF ? dp[N][P][P][P][P][P] : -1;
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
