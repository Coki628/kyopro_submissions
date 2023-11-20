/*
・きっちり自力AC！
・グリッドBFS
・グリッドBFSを少しいじって、連結成分毎に総和を数える。
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

void solve() {
    ll H, W;
    cin >> H >> W;
    auto grid = listnd(H, W, 0);
    rep(h, H) {
        rep(w, W) {
            cin >> grid[h][w];
        }
    }

    auto res = list2d(H, W, INF);
    auto bfs = [&](const vector<pii> &src) {
        ll sm = 0;
        queue<pii> que;
        for (auto [h, w] : src) {
            que.push({h, w});
            res[h][w] = 0;
        }
        while (!que.empty()) {
            auto [h, w] = que.front();
            que.pop();
            sm += grid[h][w];
            for (auto [dh, dw] : dir4) {
                int nh = h + dh;
                int nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                if (grid[nh][nw] == 0) continue;
                if (res[nh][nw] == INF) {
                    res[nh][nw] = res[h][w] + 1;
                    que.push({nh, nw});
                }
            }
        }
        return sm;
    };
    ll ans = 0;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == 0 or res[h][w] < INF) continue;
            ll res = bfs({{h, w}});
            chmax(ans, res);
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
