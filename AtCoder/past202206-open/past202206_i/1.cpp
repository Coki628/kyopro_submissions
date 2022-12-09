/*
・自力AC！
・ダイクストラ、BFS
・dp[h][w][d] := 位置(h,w)に荷物があって、自分がd(隣接上下左右4通り)にいる時の最小コスト
　とすると、荷物を押す遷移と他の3箇所に移動する遷移みたいになる。これをダイクストラする。
　他の3箇所に移動する時は毎回BFSして移動コストチェックした。
　この時、荷物のあるマスを一時的に通れないように＃にしておく。
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

#include "grid/bfs.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    pll a, s, g;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == 'a') {
                a = {h, w};
            } else if (grid[h][w] == 's') {
                s = {h, w};
            } else if (grid[h][w] == 'g') {
                g = {h, w};
            }
        }
    }
    // 左右上下
    auto dp = listnd(H, W, 4, INF);
    auto [ah, aw] = a;
    grid[ah][aw] = '#';
    auto res = bfs(grid, {s});
    grid[ah][aw] = '.';
    using P = tuple<ll, ll, ll, ll>;
    priority_queue<P, vector<P>, greater<P>> que;
    rep(nd, 4) {
        auto [dh, dw] = dir4[nd];
        ll nh = ah + dh, nw = aw + dw;
        if (nh < 0 or nw < 0 or nh >= H or nw >= W)
            continue;
        if (grid[nh][nw] == '#')
            continue;
        if (chmin(dp[nh][nw][nd], res[nh][nw])) {
            que.push({res[nh][nw], ah, aw, nd});
        }
    }
    while (que.size()) {
        auto [cc, ch, cw, d] = que.top();
        que.pop();
        // 荷物を押す
        ll revd = d % 2 == 0 ? d + 1 : d - 1;
        auto [dh, dw] = dir4[revd];
        ll nh = ch + dh, nw = cw + dw;
        rep(_, 1) {
            if (nh < 0 or nw < 0 or nh >= H or nw >= W)
                continue;
            if (grid[nh][nw] == '#')
                continue;
            if (chmin(dp[nh][nw][d], cc + 1)) {
                que.push({cc + 1, nh, nw, d});
            }
        }
        // 他の3箇所に移動
        tie(dh, dw) = dir4[d];
        ll sh = ch + dh, sw = cw + dw;
        assert(!(sh < 0 or sw < 0 or sh >= H or sw >= W));
        assert(!(grid[sh][sw] == '#'));
        grid[ch][cw] = '#';
        auto res = bfs(grid, {{sh, sw}});
        grid[ch][cw] = '.';
        rep(nd, 4) {
            if (nd == d)
                continue;
            auto [dh, dw] = dir4[nd];
            ll nh = ch + dh, nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W)
                continue;
            if (grid[nh][nw] == '#')
                continue;
            ll nc = res[nh][nw];
            if (nc == INF)
                continue;
            if (chmin(dp[ch][cw][nd], cc + nc)) {
                que.push({cc + nc, ch, cw, nd});
            }
        }
    }
    ll ans = INF;
    rep(d, 4) {
        chmin(ans, dp[g.first][g.second][d]);
    }
    if (ans == INF)
        ans = -1;
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
