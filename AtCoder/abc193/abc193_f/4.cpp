/*
ライブラリ整備：燃やす埋める
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

#include "graph/PSP.hpp"

void solve() {
    ll H, W;
    cin >> H;
    W = H;
    vector<string> grid(H);
    cin >> grid;

    ll N = H * W;
    ll total = H * (W - 1) + W * (H - 1);
    PSP psp(N, false);
    rep(h, H) {
        rep(w, W) {
            ll i = gridtoid(h, w, W);
            ll useb = 0, usew = 0;
            // 色が決まってる時はカットで選びたくない方をINFに
            if (grid[h][w] == 'B') {
                usew = INF;
            } else if (grid[h][w] == 'W') {
                useb = INF;
            }
            // 市松の片方は条件を逆にする
            if ((h + w) % 2 == 0) {
                swap(useb, usew);
            }
            // マス(h,w)を黒にする/白にする(偶奇により逆)
            psp.add(i, useb, usew);

            // 隣接マス同士の条件
            if (h != H - 1) {
                ll j = gridtoid(h + 1, w, W);
                // (h,w)が白、(h+1,w)も白ならコスト1を負う(偶奇により白黒逆)
                psp.a_right_and_b_left_then(i, j, 1);
                // (h,w)が黒、(h+1,w)も黒ならコスト1を負う(偶奇により白黒逆)
                psp.a_right_and_b_left_then(j, i, 1);
            }
            if (w != W - 1) {
                ll j = gridtoid(h, w + 1, W);
                // (h,w)が白、(h,w+1)も白ならコスト1を負う(偶奇により白黒逆)
                psp.a_right_and_b_left_then(i, j, 1);
                // (h,w)が黒、(h,w+1)も黒ならコスト1を負う(偶奇により白黒逆)
                psp.a_right_and_b_left_then(j, i, 1);
            }
        }
    }
    // 最大利得から最小コストを引く
    ll ans = total - psp.solve();
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
