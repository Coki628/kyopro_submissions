/*
・自力AC！やったね！
・グリッドDP
・その行・列の反転有無を状態に持って、次の行/列を反転させるかみたいに遷移させる。
　だいたいの方針は割とすんなり立ったんだけど、
　状態管理で遷移先のマス(if文で見るところ)をちゃんと反転考慮してなかったり、
　遷移先の状態変化が0/1じゃなくて今状態からの反転になってたり、
　細部詰め切れてなくて結構危なかった。終了6分前くらいに無事AC。
・ちょっと気になったことがあって実験。
　Python時代は次元の深いDPは小さい添字をなるべく前にしてたけど、
　C++だとだいたい通るのであんま気にしてなかった。
　今回ちょうど次元が深いので、試しに小さいのを前と後ろで試してみた。(こっちは後ろ)
　結果、C++でもかなり差が出ると判明。
　前が小さいとメモリ207MBの0.36秒、後ろが小さいとメモリ613MBの1.05秒。
　こういう2択の状態持つやつはそれが後ろのが自分的にはやりやすい(ループと順序が合うので)んだけど、
　ここまで差が出るならちゃんと小さい添字前に出した方がいいな。。
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

    auto dp = listnd(H, W, 2, 2, INF);
    dp[0][0][0][0] = 0;
    dp[0][0][1][0] = A[0];
    dp[0][0][0][1] = B[0];
    dp[0][0][1][1] = A[0] + B[0];
    rep(h, H) {
        rep(w, W) {
            rep(i, 2) {
                rep(j, 2) {
                    ll cur = grid[h][w] ^ i ^ j;
                    if (h+1 < H) {
                        if (cur == (grid[h+1][w]^j)) {
                            chmin(dp[h+1][w][0][j], dp[h][w][i][j]);
                        } else {
                            chmin(dp[h+1][w][1][j], dp[h][w][i][j]+A[h+1]);
                        }
                    }
                    if (w+1 < W) {
                        if (cur == (grid[h][w+1]^i)) {
                            chmin(dp[h][w+1][i][0], dp[h][w][i][j]);
                        } else {
                            chmin(dp[h][w+1][i][1], dp[h][w][i][j]+B[w+1]);
                        }
                    }
                }
            }
        }
    }
    ll ans = INF;
    rep(i, 2) {
        rep(j, 2) {
            chmin(ans, dp[H-1][W-1][i][j]);
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
