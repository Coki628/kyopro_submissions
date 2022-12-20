/*
・自力AC。
・一応グリッド回転はライブラリの用意があったので、
　だるいけど回転させながら愚直にチェックした。
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

#include "grid/rot90.hpp"

void solve() {
    auto grid = listnd(2, 2, 0);
    cin >> grid;
    rep(_, 4) {
        if (grid[0][0] < grid[0][1] and grid[0][0] < grid[1][0] and
            grid[0][1] < grid[1][1] and grid[1][0] < grid[1][1]) {
            YES();
            return;
        }
        grid = rot90(grid);
    }
    NO();
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
