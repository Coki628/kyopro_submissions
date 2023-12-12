/*
ライブラリ整備：燃やす埋める
・利得のままでも求まるような条件を作った。
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
    PSP psp(N);
    rep(h, H) {
        rep(w, W) {
            int i = gridtoid(h, w, W);
            ll useb = 0, usew = 0;
            // 色が決まってる時はカットで選びたくない方の利得を-INFに
            if (grid[h][w] == 'B') {
                usew = -INF;
            } else if (grid[h][w] == 'W') {
                useb = -INF;
            }
            // 市松の片方は条件を逆にする
            if ((h + w) % 2 == 0) {
                swap(useb, usew);
            }
            // マス(h,w)を黒にする/白にする(偶奇により逆)
            psp.add(i, useb, usew);

            // 隣接マス同士の条件
            if (h != H - 1) {
                int j = gridtoid(h + 1, w, W);
                // i,jが両方右なら白黒が異なるので利得1
                psp.all_right_then({i, j}, 1);
                // i,jが両方左なら白黒が異なるので利得1
                psp.all_left_then({i, j}, 1);
            }
            if (w != W - 1) {
                int j = gridtoid(h, w + 1, W);
                psp.all_right_then({i, j}, 1);
                psp.all_left_then({i, j}, 1);
            }
        }
    }
    ll ans = psp.solve();
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
