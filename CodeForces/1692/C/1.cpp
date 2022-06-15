/*
・きっちり自力AC。
・真ん中と周囲で5マス見る。
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
    ll N = 8;
    vector<string> grid(N);
    rep(i, N) cin >> grid[i];

    rep(i, 1, N-1) {
        rep(j, 1, N-1) {
            if (
                grid[i][j] == '#' and
                grid[i-1][j-1] == '#' and
                grid[i+1][j+1] == '#' and
                grid[i-1][j+1] == '#' and
                grid[i+1][j-1] == '#'
            ) {
                print(mkp(i+1, j+1));
                return;
            }
        }
    }
    assert(0);
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
