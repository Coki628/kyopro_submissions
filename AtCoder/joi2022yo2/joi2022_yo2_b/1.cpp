/*
・きっちり自力AC！
・グリッドBFSちょっといじる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

// グリッドBFS
vvl bfs(const vector<string> &grid, const vector<pii> &src, char invalid='#') {

    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(H, W, INF);
    const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    queue<tuple<int, int, char>> que;
    for (auto [h, w] : src) {
        que.push({h, w, grid[h][w]});
        res[h][w] = 0;
    }
    while (!que.empty()) {
        auto [h, w, c] = que.front(); que.pop();
        for (auto [dh, dw] : directions) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (grid[nh][nw] == c) continue;
            if (res[nh][nw] == INF) {
                res[nh][nw] = res[h][w] + 1;
                que.push({nh, nw, grid[nh][nw]});
            }
        }
    }
    return res;
}


void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    rep(i, H) cin >> grid[i];

    auto res = bfs(grid, {{0, 0}});
    ll ans = res[H-1][W-1];
    if (ans >= INF) ans = -1;
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
