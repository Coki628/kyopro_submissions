/*
・自力AC！
・グリッド、実装
・条件を見る限り、L字を作れるとすれば場所は決まっていて、
　別の重ね方があったりはしなそう。であれば愚直に全部見れば良さそう。
　4マス毎に見て行って、その4マスを使うL字4パターンについてチェック、
　うまくいけば消す、消した所から8方向見て、周辺に重複があったりしたら即NG。
　全部終わって、残ってる#があった場合もNG。
　これで通った。結構神経使ったけど、一発で通って良かった。
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

#include "grid/constants/dir8.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    auto check = [&](pll a, pll b, pll c) {
        auto [h1, w1] = a;
        auto [h2, w2] = b;
        auto [h3, w3] = c;
        if (grid[h1][w1] == '*' and grid[h2][w2] == '*' and grid[h3][w3] =='*') {
            grid[h1][w1] = grid[h2][w2] = grid[h3][w3] = '.';
            for (auto hw : {a, b, c}) {
                auto [ch, cw] = hw;
                for (auto [dh, dw] : dir8) {
                    ll nh = ch + dh;
                    ll nw = cw + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (grid[nh][nw] == '*') {
                        return false;
                    }
                }
            }
        }
        return true;
    };
    rep(h1, H - 1) {
        rep(w1, W - 1) {
            ll h2 = h1 + 1;
            ll w2 = w1 + 1;
            if (
                !check({h1, w1}, {h1, w2}, {h2, w1}) or 
                !check({h1, w1}, {h1, w2}, {h2, w2}) or 
                !check({h1, w1}, {h2, w1}, {h2, w2}) or 
                !check({h1, w2}, {h2, w1}, {h2, w2})
            ) {
                NO();
                return;
            }
        }
    }
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '*') {
                NO();
                return;
            }
        }
    }
    YES();
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
