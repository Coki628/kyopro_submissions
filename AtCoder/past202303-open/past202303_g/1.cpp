/*
・きっちり自力AC！
・グリッド
・隣接を見て、全部setに詰めればOK。
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
    ll H, W;
    cin >> H >> W;
    auto grid = listnd(H, W, 0LL);
    rep(h, H) {
        cin >> grid[h];
    }

    set<pll> se;
    rep(h, H) {
        rep(w, W) {
            if (h + 1 < H) {
                ll a = grid[h][w];
                ll b = grid[h + 1][w];
                if (a > b) swap(a, b);
                se.insert({a ,b});
            }
            if (w + 1 < W) {
                ll a = grid[h][w];
                ll b = grid[h][w + 1];
                if (a > b) swap(a, b);
                se.insert({a ,b});
            }
        }
    }
    print(se, "\n");
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
