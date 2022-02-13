/*
・FPS演習
・FPS、繰り返し二乗法
・3乗DPが線形log2つまで落とせるのはすごいけど、これはTLE。。
　制約がきつくて、Nは30万だけど和のMは100万だからね。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"
#include "math/fps/pow.hpp"

void solve() {
    ll N, M, D1, D2;
    cin >> N >> M >> D1 >> D2;

    // auto dp = list2d<mint>(N, M+1, 0);
    // rep(i, 1, M+1) dp[0][i] = 1;
    // rep(i, N-1) {
    //     rep(j, M+1) {
    //         rep(k, D1, D2+1) {
    //             if (j+k <= M) {
    //                 dp[i+1][j+k] += dp[i][j];
    //             }
    //         }
    //     }
    // }
    // mint ans = sum(dp[N-1]);
    // print(ans);

    FPS<mint> F(M+1), G(M+1);
    rep(i, 1, M+1) F[i] = 1;
    rep(i, D1, D2+1) {
        G[i] = 1;
    }
    F *= pow(G, N-1, M+1);
    F.shrink(M+1);
    mint ans = sum(F);
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
