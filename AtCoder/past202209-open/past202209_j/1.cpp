/*
・自力ならず。。しょーもないケアレスミスを。。
・幾何、円、長方形
・円の方程式、式変形、3点と角度
・最終的にぼぼ方針合ってたけど、何故かWAが取れなかった。
　結局、横側でも使う円の面積Sを縦側で直接引いちゃってたせいで、
　横の計算する時Sの値変わっちゃってる時があるからバグるっていう、
　まあしょーもないミス。
　これ粘着して結局バグ取れずに終了は良くなかったなー。。。
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

#include "geometry/angle.hpp"

void solve() {
    ld H, W, D;
    cin >> H >> W >> D;

    // 半径Dの円の面積
    ld S = D * D * PI;
    ld sub = 0;
    if (D * 2 > H) {
        ld y = H / 2;
        ld x1 = sqrt(pow(D, 2) - pow(y, 2));
        ld x2 = -x1;
        ld len = abs(x1 - x2);
        // 内包判定
        if (len > W) {
            print(1);
            return;
        }
        ld deg = angle<ld>({x1, y}, {0, 0}, {x2, y});
        // 扇の面積
        ld arc = S * (deg / 360);
        // 三角形の面積
        ld tri = len * y / 2;
        // 差し引くべき部分
        sub += (arc - tri) * 2;
    }
    if (D * 2 > W) {
        ld x = W / 2;
        ld y1 = sqrt(pow(D, 2) - pow(x, 2));
        ld y2 = -y1;
        ld len = abs(y1 - y2);
        // 内包判定
        if (len > H) {
            print(1);
            return;
        }
        ld deg = angle<ld>({x, y2}, {0, 0}, {x, y1});
        // 扇の面積
        ld arc = S * (deg / 360);
        // 三角形の面積
        ld tri = len * x / 2;
        // 差し引くべき部分
        sub += (arc - tri) * 2;
    }
    S -= sub;
    ld ans = S / (H * W);
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
