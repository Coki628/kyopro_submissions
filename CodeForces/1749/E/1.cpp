/*
・これはWAになったDP方針。
　頑張って書いたので一応残しておこうか…。
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

#include "grid/transpose.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    rep(i, H) {
        cin >> grid[i];
    }

    grid = transpose(grid);
    swap(H, W);
    ll mn = INF;
    vector<pll> vec;
    rep(p, 2) {
        auto dp = listnd(H, W, pll{INF, -1});
        rep(w, W) {
            if (w%2 == p) {
                if (w == 0) {
                    if (grid[0][w+1] == '.' and grid[1][w] == '.') {
                        dp[0][w] = {grid[0][w] == '.', -1};
                    }
                } elif (w == W-1) {
                    if (grid[0][w-1] == '.' and grid[1][w] == '.') {
                        dp[0][w] = {grid[0][w] == '.', -1};
                    }
                } else {
                    if (grid[0][w-1] == '.' and grid[0][w+1] == '.' and grid[1][w] == '.') {
                        dp[0][w] = {grid[0][w] == '.', -1};
                    }
                }
            }
        }
        rep(h, H-1) {
            rep(w, W) {
                if (dp[h][w].first == INF) continue;
                if ((h+w)%2 == p) {
                    if (w+1 <= W-1) {
                        if (grid[h+1][w] == '.' and grid[h][w+1] == '.') {
                            if (w+2 > W-1 or grid[h+1][w+2] == '.') {
                                ll nxval = dp[h][w].first + (grid[h+1][w+1] == '.');
                                if (nxval < dp[h+1][w+1].first) {
                                    dp[h+1][w+1] = {nxval, w};
                                }
                            }
                        }
                    }
                    if (w-1 >= 0) {
                        if (grid[h+1][w] == '.' and grid[h][w-1] == '.') {
                            if (w-2 < 0 or grid[h+1][w-2] == '.') {
                                ll nxval = dp[h][w].first + (grid[h+1][w-1] == '.');
                                if (nxval < dp[h+1][w-1].first) {
                                    dp[h+1][w-1] = {nxval, w};
                                }
                            }
                        }
                    }
                }
            }
        }
        rep(w, W) {
            if (chmin(mn, dp[H-1][w].first)) {
                vector<pll> tmp;
                ll curw = w, curh = H-1;
                while (curh >= 0) {
                    tmp.eb(curh, curw);
                    curw = dp[curh][curw].second;
                    curh--;
                }
                vec = tmp;
            }
        }
    }
    if (mn < INF) {
        vector<string> ans = grid;
        for (auto [h, w] : vec) {
            ans[h][w] = '#';
        }
        ans = transpose(ans);
        YES();
        print(ans, '\n');
    } else {
        NO();
    }
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
