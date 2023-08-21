/*
・自力ならず。。
・本番中まとまらず、終了後整えたものを投げてもTLE…。
　400万にsetのlog乗るとつらいのかそもそも壊れてるのか判別がついてない。
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

    ll M = 26;
    auto rows = listnd(H, M, set<ll>());
    auto cols = listnd(W, M, set<ll>());
    // {ccnt, num, row or col}
    set<array<ll, 3>> se;
    vector<ll> szh(H), szw(W);
    rep(h, H) {
        rep(w, W) {
            rows[h][grid[h][w] - 'a'].insert(w);
            cols[w][grid[h][w] - 'a'].insert(h);
        }
    }
    rep(h, H) {
        ll ccnt = 0;
        rep(c, M) {
            if (rows[h][c].size()) {
                ccnt++;
            }
        }
        se.insert({ccnt, h, 0});
        szh[h] = ccnt;
    }
    rep(w, W) {
        ll ccnt = 0;
        rep(c, M) {
            if (cols[w][c].size()) {
                ccnt++;
            }
        }
        se.insert({ccnt, w, 1});
        szw[w] = ccnt;
    }

    ll ans = H * W;
    while (1) {
        vector<array<ll, 3>> tmp;
        while (se.size() and (*se.begin())[0] == 1) {
            auto [sz, num, rc] = *se.begin();
            se.erase(se.begin());
            if (rc == 0) {
                ll h = num;
                rep(c, M) {
                    if (rows[h][c].size() >= 2) {
                        tmp.pb({h, c, rc});
                    }
                }
            } else {
                ll w = num;
                rep(c, M) {
                    if (cols[w][c].size() >= 2) {
                        tmp.pb({w, c, rc});
                    }
                }
            }
        }
        if (tmp.empty()) break;
        for (auto [num, c, rc] : tmp) {
            if (rc == 0) {
                ll h = num;
                for (auto w : rows[h][c]) {
                    cols[w][c].erase(h);
                    ans--;
                    if (cols[w][c].empty() and se.count({szw[w], w, 1})) {
                        se.erase({szw[w], w, 1});
                        szw[w]--;
                        se.insert({szw[w], w, 1});
                    }
                }
            } else {
                ll w = num;
                for (auto h : cols[w][c]) {
                    rows[h][c].erase(w);
                    ans--;
                    if (rows[h][c].empty() and se.count({szh[h], h, 0})) {
                        se.erase({szh[h], h, 0});
                        szh[h]--;
                        se.insert({szh[h], h, 0});
                    }
                }
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
