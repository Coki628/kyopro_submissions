/*
・グリッド愚直シミュ
・一応250点にはなってたけど、これBで問うのは結構酷だよね。
　駆け出しの頃じゃ実装方針そうそうまとまらないと思う。
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

void solve() {
    ll H, W, N;
    cin >> H >> W >> N;
    vector<string> grid(H, string(W, '.'));

    const vector<pii> dir4 = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    ll h = 0, w = 0, d = 0;
    rep(_, N) {
        if (grid[h][w] == '.') {
            grid[h][w] = '#';
            d = (d + 1) % 4;
        } else {
            grid[h][w] = '.';
            d = modulo(d - 1, 4LL);
        }
        auto [dh, dw] = dir4[d];
        h += dh, w += dw;
        h = modulo(h, H);
        w = modulo(w, W);
    }
    print(grid, "\n");
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
