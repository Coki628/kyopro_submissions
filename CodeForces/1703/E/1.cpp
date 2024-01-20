/*
・自力AC！
・グリッド回転
・90度ずつ4回回して重なる所を集計する。
　最後に割る4しても合うけど、要は同一視される場所を無視して
　左上1/4くらいだけ数える感じでもよかったと思う。
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

#include "grid/rot90.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<string> grid(N);
    cin >> grid;

    auto C = listnd(N, N, 2, 0);
    rep(_, 4) {
        rep(h, N) {
            rep(w, N) {
                C[h][w][grid[h][w] - '0']++;
            }
        }
        grid = rot90(grid);
    }
    ll ans = 0;
    rep(h, N) {
        rep(w, N) {
            ans += min(C[h][w][0], C[h][w][1]);
        }
    }
    ans /= 4;
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
