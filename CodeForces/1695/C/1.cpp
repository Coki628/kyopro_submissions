/*
・きっちり自力AC！
・グリッドDP
・偶奇でちょうど0にできないやつは先に弾く。
　それ以外なら、最大と最小求めるグリッドDPして結果0以上と0以下になれるなら、
　よしなに調節して0にできる。(と信じてぶん投げると通る)
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
    ll H, W;
    cin >> H >> W;
    vvl grid(H);
    rep(i, H) {
        grid[i] = LIST(W);
    }

    if ((H+W)%2 == 0) {
        NO();
        return;
    }

    auto dp1 = list2d(H+1, W+1, INF);
    auto dp2 = list2d(H+1, W+1, -INF);
    dp1[1][0] = 0;
    dp1[0][1] = 0;
    dp2[1][0] = 0;
    dp2[0][1] = 0;
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            chmin(dp1[i][j], dp1[i-1][j] + grid[i-1][j-1]);
            chmin(dp1[i][j], dp1[i][j-1] + grid[i-1][j-1]);
            chmax(dp2[i][j], dp2[i-1][j] + grid[i-1][j-1]);
            chmax(dp2[i][j], dp2[i][j-1] + grid[i-1][j-1]);
        }
    }
    if (dp1[H][W] <= 0 and dp2[H][W] >= 0) {
        YES();
    } else {
        NO();
    }
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
