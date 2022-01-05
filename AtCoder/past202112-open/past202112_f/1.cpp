/*
・グリッドBFS
・8方向から使える向きだけを渡す。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

// 8方向
const vector<pii> directions8 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

// グリッドBFS
vvl bfs(const vector<string> &grid, const vector<pii> &src, vector<pii> directions) {

    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(H, W, INF);
    // const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    queue<pii> que;
    for (auto [h, w] : src) {
        que.push({h, w});
        res[h][w] = 0;
    }
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop();
        for (auto [dh, dw] : directions) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            // if (grid[nh][nw] == invalid) continue;
            if (res[nh][nw] == INF) {
                res[nh][nw] = res[h][w] + 1;
                que.push({nh, nw});
            }
        }
    }
    return res;
}

void solve() {
    ll sh, sw;
    cin >> sh >> sw;
    sh--; sw--;
    vector<string> S(3);
    rep(i, 3) {
        cin >> S[i];
    }

    vector<pii> directions;
    ll ch = 1, cw = 1;
    rep(i, 8) {
        auto [dh, dw] = directions8[i];
        ll nh = ch+dh;
        ll nw = cw+dw;
        if (S[nh][nw] =='#') {
            directions.eb(dh, dw);
        }
    }
    ll N = 9;
    vector<string> grid(N, string(N, '.'));
    auto res = bfs(grid, {{sh, sw}}, directions);
    ll ans = 0;
    rep(i, N) {
        rep(j, N) {
            if (res[i][j] < INF) ans++;
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
