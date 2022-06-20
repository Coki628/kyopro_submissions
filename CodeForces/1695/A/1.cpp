/*
・きっちり自力AC！
・最大値マスの四方からの距離を見る。
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

    pll mxi;
    ll mx = -INF;
    rep(h, H) {
        rep(w, W) {
            if (chmax(mx, grid[h][w])) {
                mxi = {h, w};
            }
        }
    }
    auto [sh, sw] = mxi;
    ll ans = max(sh+1, H-sh) * max(sw+1, W-sw);
    print(ans);
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
