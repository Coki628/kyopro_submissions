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
#include "common/input.hpp"
#include "common/print.hpp"

#include "string/RollingHash2D.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;
    ll R, C;
    cin >> R >> C;
    vector<string> ptn(R);
    cin >> ptn;

    if (R > H or C > W) return;

    RollingHash2D rh2d;
    auto hashs = rh2d.get_hashs(grid, R, C);
    auto target = rh2d.get_hash(ptn);

    vector<pll> ans;
    rep(i, H - R + 1) {
        rep(j, W - C + 1) {
            if (hashs[i][j] == target) {
                ans.pb({i, j});
            }
        }
    }
    if (ans.size()) {
        print(ans, "\n");
    }
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
