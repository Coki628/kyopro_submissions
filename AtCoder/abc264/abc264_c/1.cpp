/*
・自力AC！
・ビット全探索
・片側ビット全探索して反対側貪欲みたいにやる。
　実装とかまあまあ面倒。こういうのある程度以上速くなんないんだよな…。
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
    ll H1, W1;
    cin >> H1 >> W1;
    auto grid1 = listnd(H1, W1, 0);
    rep(i, H1) {
        rep(j, W1) {
            cin >> grid1[i][j];
        }
    }
    ll H2, W2;
    cin >> H2 >> W2;
    auto grid2 = listnd(H2, W2, 0);
    rep(i, H2) {
        rep(j, W2) {
            cin >> grid2[i][j];
        }
    }

    rep(bit, 1LL<<W1) {
        if (popcount(bit) != W2) continue;
        vector<ll> ids;
        rep(i, W1) {
            if (bit>>i & 1) {
                ids.eb(i);
            }
        }
        ll h2 = 0;
        rep(h1, H1) {
            vector<int> col;
            for (auto w1 : ids) {
                col.eb(grid1[h1][w1]);
            }
            if (h2 < H2 and col == grid2[h2]) h2++;
        }
        if (h2 == H2) {
            Yes();
            return;
        }
    }
    No();
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
