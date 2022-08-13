/*
・実装。なんかうまいループ作る。
　これB結構むずいような。(かといってCって感じでもないんだけど)
・なんかTL見てたら結構愚直お絵かきした人も多かったぽい。
　あと中心からチェビシェフ距離だって。確かにー。
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
    ll N = 15;
    auto grid = list2d(N, N, 0);
    rep(d, 0, N/2, 2) {
        ll l = d;
        ll r = N - d;
        rep(x, l, r) {
            grid[x][l] = 1;
            grid[x][r-1] = 1;
            grid[l][x] = 1;
            grid[r-1][x] = 1;
        }
    }

    ll h, w;
    cin >> h >> w;
    h--; w--;
    if (grid[h][w]) print("black");
    else print("white");
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
