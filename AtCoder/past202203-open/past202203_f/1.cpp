/*
・各マスから上下左右見て、州が違うかつ色が同じ箇所が1つでもあればNo。
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
    ll H, W, N;
    cin >> H >> W >> N;
    vvl grid(H);
    rep(i, H) {
        grid[i] = LIST(W);
        rep(j, W) {
            grid[i][j]--;
        }
    }
    auto C = LIST(N);

    rep(ch, H) {
        rep(cw, W) {
            for (auto [dh, dw] : dir4) {
                ll nh = ch + dh;
                ll nw = cw + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                if (
                    grid[ch][cw] != grid[nh][nw] and C[grid[ch][cw]] == C[grid[nh][nw]]
                ) {
                    No();
                    return;
                }
            }
        }
    }
    Yes();
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
