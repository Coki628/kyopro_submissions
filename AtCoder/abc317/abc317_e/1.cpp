/*
・きっちり自力AC！
・目線を障害物Bみたいな扱いにしてグリッドを予め改変してからBFS。
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

// グリッドBFS
vvl bfs(const vector<string> &grid, const vector<pii> &src) {
    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(H, W, INF);
    queue<pii> que;
    for (auto [h, w] : src) {
        que.push({h, w});
        res[h][w] = 0;
    }
    while (!que.empty()) {
        auto [h, w] = que.front();
        que.pop();
        for (auto [dh, dw] : dir4) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (grid[nh][nw] != '.' and grid[nh][nw] != 'G') continue;
            if (res[nh][nw] == INF) {
                res[nh][nw] = res[h][w] + 1;
                que.push({nh, nw});
            }
        }
    }
    return res;
}

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    ll sh, sw, gh, gw;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == 'S') {
                sh = h, sw = w;
            }
            if (grid[h][w] == 'G') {
                gh = h, gw = w;
            }
            if (grid[h][w] == '>') {
                rep(cw, w + 1, W) {
                    if (grid[h][cw] == '.' or grid[h][cw] == '*') {
                        grid[h][cw] = '*';
                    } else {
                        break;
                    }
                }
            }
            if (grid[h][w] == '<') {
                rep(cw, w - 1, -1, -1) {
                    if (grid[h][cw] == '.' or grid[h][cw] == '*') {
                        grid[h][cw] = '*';
                    } else {
                        break;
                    }
                }
            }
            if (grid[h][w] == 'v') {
                rep(ch, h + 1, H) {
                    if (grid[ch][w] == '.' or grid[ch][w] == '*') {
                        grid[ch][w] = '*';
                    } else {
                        break;
                    }
                }
            }
            if (grid[h][w] == '^') {
                rep(ch, h - 1, -1, -1) {
                    if (grid[ch][w] == '.' or grid[ch][w] == '*') {
                        grid[ch][w] = '*';
                    } else {
                        break;
                    }
                }
            }
        }
    }

    auto res = bfs(grid, {{sh, sw}});
    ll ans = res[gh][gw] < INF ? res[gh][gw] : -1;
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
