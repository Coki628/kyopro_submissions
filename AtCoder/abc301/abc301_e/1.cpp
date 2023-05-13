/*
・きっちり自力AC！
・BFS、bitDP、TSP
・お菓子マス集めてTSP。その状態からゴールに行けるならpopcountでchmax。
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
    ll H, W, T;
    cin >> H >> W >> T;
    vector<string> grid(H);
    cin >> grid;

    vector<vvl> dist;
    map<ll, pll> mp;
    ll k = 0;
    pll s, g;
    vvl dists, distg;
    rep(i, H) {
        rep(j, W) {
            if (grid[i][j] == 'S' or grid[i][j] == 'G' or grid[i][j] == 'o') {
                auto res = bfs(grid, {{i, j}});
                if (grid[i][j] == 'S') {
                    s = {i, j};
                    dists = res;
                } else if (grid[i][j] == 'G') {
                    g = {i, j};
                    distg = res;
                } else {
                    mp[k++] = {i, j};
                    dist.eb(res);
                }
            }
        }
    }

    auto [gh, gw] = g;
    if (dists[gh][gw] > T) {
        print(-1);
        return;
    }
    ll ans = 0;
    ll L = k;
    auto dp = listnd(L, 1 << L, INF);
    rep(i, L) {
        auto [h, w] = mp[i];
        ll cost = dists[h][w];
        dp[i][1 << i] = cost;
    }
    rep(bit, 1 << L) {
        rep(i, L) {
            if (dp[i][bit] == INF) continue;
            if (!(bit >> i & 1)) continue;

            ll gcost = dist[i][gh][gw];
            if (dp[i][bit] + gcost <= T) {
                chmax(ans, (ll)popcount(bit));
            }

            rep(j, L) {
                if (bit >> j & 1) continue;
                auto [nh, nw] = mp[j];
                ll ncost = dist[i][nh][nw];
                chmin(dp[j][bit | 1 << j], dp[i][bit] + ncost);
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
