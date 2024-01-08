/*
参考：https://atcoder.jp/contests/abc335/editorial/9027
・グリッド、実装、渦巻き
・もたついたので、公式解のやり方を参考に。
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

void solve() {
    ll N;
    cin >> N;
    ll H = N, W = N;
    auto grid = listnd(H, W, string());
    grid[H / 2][W / 2] = "T";

    // →, ↓, ←, ↑
    vector<pll> ds = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    ll ch = 0, cw = 0, cur = 1, d = 0;
    grid[ch][cw] = tostr(cur++);
    while (cur < H * W) {
        auto [dh, dw] = ds[d];
        ll nh = ch + dh, nw = cw + dw;
        if (nh < 0 or nw < 0 or nh >= H or nw >= W or grid[nh][nw] != "") {
            d = (d + 1) % 4;
        } else {
            grid[nh][nw] = tostr(cur++);
            ch = nh, cw = nw;
        }
        // debug(grid);
    }
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
