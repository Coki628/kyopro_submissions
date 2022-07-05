/*
・自力ならず。。
・グリッド、構築
・なんかL字4分割みたいなので行ける気がして、
　それベースで何とかしようと頑張ってしまったのが良くなかった…。
・2*2毎に市松みたいなやつをちょっとずらしたやつがぴったりハマる。
　思いつけなかったので負け…。
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
    auto grid = list2d(H+2, W+2, -1);

    rep(i, H+2) {
        rep(j, W+2) {
            grid[i][j] = (i/2+j/2) % 2;
        }
    }
    rep(i, 1, H+1) {
        print(subarray(grid[i], 1, W+1));
    }
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
