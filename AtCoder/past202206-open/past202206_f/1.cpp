/*
・自力AC！
・ブロックの落下を高速に表すのに、列毎にBITにぶたん生やしたんだけど、
　これ制約的に愚直シミュで間に合うよね。。
　行列逆にして前後も逆にしてとか色々しんどかったよ…。
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

    vector<BIT<ll>> bit(W, BIT<ll>{H});
    rep(w, W) {
        rep(h, H) {
            if (grid[h][w]) {
                bit[w].add(H - h - 1, 1);
            }
        }
    }
    ll N;
    cin >> N;
    rep(_, N) {
        ll r, c;
        cin >> r >> c;
        r--;
        c--;

        ll i = bit[c].bisearch_fore(0, H - 1, H - r);
        if (i != -1) {
            bit[c].add(i, -1);
        }
    }
    vvl adj(W);
    rep(w, W) {
        rep(h, H) {
            if (bit[w][H - h - 1]) {
                adj[w].eb(grid[h][w]);
            }
        }
        reverse(ALL(adj[w]));
        while (adj[w].size() < H) {
            adj[w].eb(0);
        }
        reverse(ALL(adj[w]));
    }
    auto ans = listnd(H, W, 0LL);
    rep(h, H) {
        rep(w, W) {
            ans[h][w] = adj[w][h];
        }
    }
    print(ans, '\n');
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
