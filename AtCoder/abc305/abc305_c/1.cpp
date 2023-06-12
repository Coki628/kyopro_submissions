/*
・きっちり自力AC。
・縦横2以上の領域と問題文にあるので、
　1つ欠けてても元の長方形の上下左右がどこまであったかは分かる。
　その長方形領域を先に取得してから欠けた場所を見つければOK。
・TLで別解として見かけたのは、2マス以上#と接している.が答えというもの。賢い。
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
    vector<string> grid(H);
    cin >> grid;

    ll l = INF, r = -INF, u = INF, d = -INF;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '#') {
                chmin(l, w);
                chmax(r, w);
                chmin(u, h);
                chmax(d, h);
            }
        }
    }
    rep(h, u, d + 1) {
        rep(w, l, r + 1) {
            if (grid[h][w] == '.') {
                print(mkp(h + 1, w + 1));
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
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
