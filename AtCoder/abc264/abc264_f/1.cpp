/*
・自力AC！やったね！
・グリッドDP
・その行・列の反転有無を状態に持って、次の行/列を反転させるかみたいに遷移させる。
　だいたいの方針は割とすんなり立ったんだけど、
　状態管理で遷移先のマス(if文で見るところ)をちゃんと反転考慮してなかったり、
　遷移先の状態変化が0/1じゃなくて今状態からの反転になってたり、
　細部詰め切れてなくて結構危なかった。終了6分前くらいに無事AC。
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
    auto A = LIST(H);
    auto B = LIST(W);
    auto grid = listnd(H, W, 0);
    rep(i, H) {
        rep(j, W) {
            char c;
            cin >> c;
            grid[i][j] = c - '0';
        }
    }

    auto dp = listnd(2, 2, H, W, INF);
    dp[0][0][0][0] = 0;
    dp[1][0][0][0] = A[0];
    dp[0][1][0][0] = B[0];
    dp[1][1][0][0] = A[0] + B[0];
    rep(h, H) {
        rep(w, W) {
            rep(i, 2) {
                rep(j, 2) {
                    ll cur = grid[h][w] ^ i ^ j;
                    if (h+1 < H) {
                        if (cur == (grid[h+1][w]^j)) {
                            chmin(dp[0][j][h+1][w], dp[i][j][h][w]);
                        } else {
                            chmin(dp[1][j][h+1][w], dp[i][j][h][w]+A[h+1]);
                        }
                    }
                    if (w+1 < W) {
                        if (cur == (grid[h][w+1]^i)) {
                            chmin(dp[i][0][h][w+1], dp[i][j][h][w]);
                        } else {
                            chmin(dp[i][1][h][w+1], dp[i][j][h][w]+B[w+1]);
                        }
                    }
                }
            }
        }
    }
    ll ans = INF;
    rep(i, 2) {
        rep(j, 2) {
            chmin(ans, dp[i][j][H-1][W-1]);
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
