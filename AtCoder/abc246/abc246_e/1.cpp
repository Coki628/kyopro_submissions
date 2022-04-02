/*
・きっちり自力AC！
・グリッド、01BFS
・斜め移動は無制限、どっち斜めかの向き切り替えにコスト1かかるとして01BFSした。
　状態も切り替え分あるから2倍持つ。
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    ll sh, sw, th, tw;
    cin >> sh >> sw;
    cin >> th >> tw;
    sh--; sw--;
    th--; tw--;

    vector<string> grid(N);
    rep(i, N) cin >> grid[i];

    auto res = list3d(2, N, N, INF);
    vvpll dirs(2);
    dirs[0] = {{-1, -1}, {1, 1}};
    dirs[1] = {{-1, 1}, {1, -1}};
    deque<array<ll, 3>> que;
    que.pb({0, sh, sw});
    que.pb({1, sh, sw});
    res[0][sh][sw] = 1;
    res[1][sh][sw] = 1;
    while (!que.empty()) {
        auto [p, h, w] = que.front(); que.pop_front();
        if (h == th and w == tw) break;
        for (auto [dh, dw] : dirs[p]) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= N or nw >= N) continue;
            if (grid[nh][nw] == '#') continue;
            if (res[p][nh][nw] > res[p][h][w]) {
                res[p][nh][nw] = res[p][h][w];
                que.push_front({p, nh, nw});
            }
        }
        if (res[1-p][h][w] > res[p][h][w]+1) {
            res[1-p][h][w] = res[p][h][w] + 1;
            que.push_back({1-p, h, w});
        }
    }
    ll ans = min(res[0][th][tw], res[1][th][tw]);
    if (ans == INF) ans = -1;
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
