/*
・きっちり自力AC！
・4方向状態持ってBFS
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

    auto res = listnd(4, H, W, INF);
    queue<array<ll, 3>> que;
    rep(d, 4) {
        que.push({d, 1, 1});
        res[d][1][1] = 0;
    }
    while (!que.empty()) {
        auto [d, h, w] = que.front();
        que.pop();
        auto [dh, dw] = dir4[d];
        int nh = h + dh;
        int nw = w + dw;
        if (grid[nh][nw] == '#') {
            rep(dd, 4) {
                auto [dh, dw] = dir4[dd];
                int nh = h + dh;
                int nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                if (grid[nh][nw] == '#') continue;
                if (res[dd][nh][nw] == INF) {
                    res[dd][nh][nw] = res[d][h][w] + 1;
                    que.push({dd, nh, nw});
                }
            }
        } else if (res[d][nh][nw] == INF) {
            res[d][nh][nw] = res[d][h][w] + 1;
            que.push({d, nh, nw});
        }
    }

    ll ans = 0;
    rep(h, H) {
        rep(w, W) {
            bool ok = false;
            rep(d, 4) {
                if (res[d][h][w] < INF) {
                    ok = true;
                    break;
                }
            }
            if (ok) ans++;
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
