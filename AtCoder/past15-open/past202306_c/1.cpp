/*
・なんとか自力AC…。今日イチじゃないけど相当苦戦した。。
・グリッド、幾何、円に対する点の内包判定、円の方程式、式変形
・今見ている点を固定すれば、式変形でその点のx座標でのy2つと、
　y座標でのx2つが求まるので、これらの内側にあるか確認。
　なんだけど、最初全然合わなくて困った。
　結局、sqrtかけた後+-入れる時に、
　+-入れる前に最後の足し引きをやってしまっていたのが原因だった。。
　幾何は毎度数学色濃くて大変。(そしてみんな強い。)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "grid/transpose.hpp"

void solve() {
    ll sx, sy, r, N;
    cin >> sx >> sy >> r >> N;

    ll H = N * 2 + 1;
    ll W = H;
    auto grid = listnd(H, W, '.');
    rep(h, H) {
        ll cy = h - N;
        if (pow(r, 2) - pow(cy - sy, 2) < 0) continue;
        ld x2 = sqrt(pow(r, 2) - pow(cy - sy, 2));
        ld x1 = -x2;
        x1 += sx, x2 += sx;
        rep(w, W) {
            ll cx = w - N;
            if (pow(r, 2) - pow(cx - sx, 2) < 0) continue;
            ld y2 = sqrt(pow(r, 2) - pow(cx - sx, 2));
            ld y1 = -y2;
            y1 += sy, y2 += sy;
            if (x1 <= cx and cx <= x2 and y1 <= cy and cy <= y2) {
                grid[h][w] = '#';
            }
        }
    }
    grid = transpose(grid);
    print(grid, "\n");
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
