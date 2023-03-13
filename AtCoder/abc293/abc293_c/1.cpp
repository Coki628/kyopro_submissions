/*
・きっちり自力AC！
・グリッド、再帰全探索
・移動回数はだいたい20回くらいなので2^20通りと雑に見積もると、全探索でいいとなる。
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
    auto grid = listnd(H, W, 0LL);
    cin >> grid;

    set<ll> used;
    ll ans = 0;
    auto rec = [&](auto &&f, ll h, ll w) -> void {
        if (h == H - 1 and w == W - 1) {
            ans++;
            return;
        }
        if (h + 1 < H and not used.count(grid[h + 1][w])) {
            used.insert(grid[h + 1][w]);
            f(f, h + 1, w);
            used.erase(grid[h + 1][w]);
        }
        if (w + 1 < W and not used.count(grid[h][w + 1])) {
            used.insert(grid[h][w + 1]);
            f(f, h, w + 1);
            used.erase(grid[h][w + 1]);
        }
    };
    used.insert(grid[0][0]);
    rec(rec, 0, 0);
    print(ans);
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
