/*
・きっちり自力AC！ランクAに昇格。
・グリッド、BFS
・各連結成分でBFSやって、成分数と辺のない方向を数える。
　DFSでもBFSでもいいと思ったけど、なんとなく均一に見て行けるBFSで。
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
#include "common/print.hpp"
#include "common/listnd.hpp"
#include "grid/constants/dir4.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    H += 2; W += 2;
    vector<string> grid(H, string(W, '.'));
    rep(i, 1, H-1) {
        rep(j, 1, W-1) {
            cin >> grid[i][j];
        }
    }

    auto visited = list2d(H, W, false);
    vector<pll> ans;
    rep(h, 1, H-1) {
        rep(w, 1, W-1) {
            if (grid[h][w] == '#' and not visited[h][w]) {
                pll cur;
                queue<pll> que;
                que.push({h, w});
                visited[h][w] = true;
                while (que.size()) {
                    auto [ch, cw] = que.front(); que.pop();
                    cur.first++;
                    for (auto [dh, dw] : dir4) {
                        ll nh = ch + dh;
                        ll nw = cw + dw;
                        if (grid[nh][nw] == '.') {
                            cur.second++;
                            continue;
                        }
                        if (not visited[nh][nw]) {
                            visited[nh][nw] = true;
                            que.push({nh, nw});
                        }
                    }
                }
                ans.eb(cur);
            }
        }
    }
    sort(ans.rbegin(), ans.rend());
    print(ans, '\n');
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
