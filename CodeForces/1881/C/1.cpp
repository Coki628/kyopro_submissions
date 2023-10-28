/*
・きっちり自力AC。
・グリッド、90度回転
・回転させた4通りから最大に合わせればOK。
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

#include "grid/rot90.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<string> grid(N);
    cin >> grid;

    auto g2 = rot90(grid);
    auto g3 = rot90(g2);
    auto g4 = rot90(g3);
    ll ans = 0;
    rep(i, N / 2) {
        rep(j, N / 2) {
            char a = grid[i][j];
            char b = g2[i][j];
            char c = g3[i][j];
            char d = g4[i][j];
            char mx = max({a, b, c, d});
            ans += (mx - a) + (mx - b) + (mx - c) + (mx - d);
        }
    }
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
