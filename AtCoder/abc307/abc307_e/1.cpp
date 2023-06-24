/*
・これは愚直DP。このままDP方針でもっと考察を進めるべきだった…。
　制約的にも数学ゲーかと思ってそっちで色々考えて悩んでしまった。
　(もっとも、実際包除で解く方針もあるらしい。)
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
    ll N, M;
    cin >> N >> M;

    auto dp = listnd(N + 1, M, M, (mint)0);
    rep(j, M) {
        dp[1][j][j] = 1;
    }
    rep(i, 1, N) {
        rep(j, M) {
            rep(k, M) {
                rep(l, M) {
                    if (j == l) continue;
                    if (i == N - 1 and k == l) continue;
                    dp[i + 1][l][k] += dp[i][j][k];
                }
            }
        }
    }
    mint ans = 0;
    rep(j, M) {
        rep(k, M) {
            ans += dp[N][j][k];
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
