/*
・さくっと自力AC。
・添字3つでDPする。問題名の通り2つのナップザック。
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
    ll N, A, B;
    cin >> N >> A >> B;
    vector<pll> WV;
    rep(i, N) {
        ll w, v;
        cin >> w >> v;
        WV.eb(w, v);
    }

    auto dp = listnd(N + 1, A + 1, B + 1, -INF);
    dp[0][0][0] = 0;
    rep(i, N) {
        auto [w, v] = WV[i];
        rep(a, A + 1) {
            rep(b, B + 1) {
                chmax(dp[i + 1][a][b], dp[i][a][b]);
                if (a + w <= A) {
                    chmax(dp[i + 1][a + w][b], dp[i][a][b] + v);
                }
                if (b + w <= B) {
                    chmax(dp[i + 1][a][b + w], dp[i][a][b] + v);
                }
            }
        }
    }
    ll ans = 0;
    rep(a, A + 1) {
        rep(b, B + 1) {
            chmax(ans, dp[N][a][b]);
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
