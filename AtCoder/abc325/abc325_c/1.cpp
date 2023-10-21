/*
・きっちり自力AC！
・グリッドBFS、8方向、連結成分
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

#include "grid/constants/dir8.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    auto res = list2d(H, W, INF);
    auto bfs = [&](int sh, int sw) {
        queue<pii> que;
        que.push({sh, sw});
        res[sh][sw] = 0;
        while (!que.empty()) {
            auto [h, w] = que.front(); que.pop();
            for (auto [dh, dw] : dir8) {
                int nh = h + dh;
                int nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                if (grid[nh][nw] == '.') continue;
                if (res[nh][nw] == INF) {
                    res[nh][nw] = res[h][w] + 1;
                    que.push({nh, nw});
                }
            }
        }
    };
    ll ans = 0;
    rep(h, H) {
        rep(w, W) {
            if (res[h][w] >= INF and grid[h][w] == '#') {
                bfs(h, w);
                ans++;
            }
        }
    }
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
