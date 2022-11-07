/*
・きっちり自力AC！
・グリッドBFS
・最初Dで詰まって先回りした時はいい方針が出なかったけど、
　D通してから改めて考えたら、出る方向4つ状態に持てばよくね？
　の考察が割とすぐ生えた。やっぱ考察する上で精神状態は大事…。
・始点から出た方向4通りを状態に持っておくと、
　始点以外で2つ以上が到達したマスがあれば、そこを使ってサイクルにできる。
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

    pii src;
    rep(i, H) {
        rep(j, W) {
            if (grid[i][j] == 'S') {
                src = {i, j};
            }
        }
    }
    auto dist = listnd(4, H, W, -1);
    queue<tuple<int, int, int>> que;
    auto [h, w] = src;
    rep(d, 4) {
        dist[d][h][w] = 0;
        auto [dh, dw] = dir4[d];
        int nh = h + dh;
        int nw = w + dw;
        if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
        if (grid[nh][nw] == '#') continue;
        dist[d][nh][nw] = 1;
        que.push({d, nh, nw});
    }
    while (!que.empty()) {
        auto [d, h, w] = que.front(); que.pop();
        for (auto [dh, dw] : dir4) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (grid[nh][nw] == '#') continue;
            if (dist[d][nh][nw] == -1) {
                dist[d][nh][nw] = dist[d][h][w] + 1;
                que.push({d, nh, nw});
            }
        }
    }
    rep(h, H) {
        rep(w, W) {
            if (pii{h, w} == src) continue;
            ll cnt = 0;
            rep(d, 4) {
                if (dist[d][h][w] != -1) {
                    cnt++;
                }
            }
            if (cnt >= 2) {
                Yes();
                return;
            }
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
