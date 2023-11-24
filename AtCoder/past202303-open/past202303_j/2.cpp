/*
・ライブラリ整備：2次元ロリハ
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

#include "string/RollingHash2D.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    ll W2 = W * 2;
    auto grid1 = listnd(H, W2, '*');
    auto grid2 = listnd(H, W, '*');
    rep(h, H) {
        rep(w, W) {
            cin >> grid1[h][w];
        }
    }
    rep(h, H) {
        rep(w, W) {
            cin >> grid2[h][w];
        }
    }
    rep(h, H) {
        rep(w, W2) {
            grid1[h][w] = grid1[h % H][w % W];
        }
    }

    RollingHash2D rh2d;
    auto hashs = rh2d.get_hashs(grid1, H, W);
    auto target = rh2d.get_hash(grid2);

    rep(i, H - H + 1) {
        rep(j, W2 - W + 1) {
            if (hashs[i][j] == target) {
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
