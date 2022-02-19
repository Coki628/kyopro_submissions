/*
・なんとか自力AC。危ない。。
・制約は大きい。なんかうまいこと座標計算しなきゃいけないのかと悩んで詰まった。
　他通して戻ってきて、もう一度考えると、
　2点間距離が2*√5より大きいと何やっても無理じゃん、となった。
　これで考える範囲が大幅に狭まったので、適当に座標の点全探索できる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    ld r5 = sqrt(5);
    ld d = hypot(x1-x2, y1-y2);
    if (d-EPS > r5*2) {
        No();
        return;
    }

    ll sx = min(x1, x2)-100;
    ll tx = max(x1, x2)+100;
    ll sy = min(y1, y2)-100;
    ll ty = max(y1, y2)+100;
    rep(cx, sx, tx) {
        rep(cy, sy, ty) {
            ld d1 = hypot(x1-cx, y1-cy);
            ld d2 = hypot(x2-cx, y2-cy);
            if (abs(d1-r5) < EPS and abs(d2-r5) < EPS) {
                Yes();
                return;
            }
        }
    }
    No();
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
