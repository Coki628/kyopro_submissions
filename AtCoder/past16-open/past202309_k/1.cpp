/*
・自力AC！
・グリッド、BFS、2次元累積和
・全てのKについてBFSする。一見2乗かかってしまいそうに思えるが、
　Kが大きくなれば踏みうるマスの数が少なくなるので、2乗にはならない。(と信じる)
　障害物に当たるかの判定は予め2次元累積和とか仕込んでおけばO(1)で済む。
　状態管理する配列は毎回生成とかしないように適切な状態戻しを行う。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "datastructure/Accumulate2D.hpp"

void solve() {
    ll H, W;
    cin >> H;
    W = H;
    vector<string> grid(H);
    cin >> grid;

    ll sh, sw;
    Accumulate2D<ll> acc(H, W);
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == 'S') {
                sh = h, sw = w;
            }
            if (grid[h][w] == 'X') {
                acc.add(h, w, 1);
            }
        }
    }
    acc.build();
    auto dist = listnd(H, W, INF);
    rep(k, 1, H) {
        auto bfs = [&](const vector<pii> &src, char invalid = 'X') {
            queue<pii> que;
            for (auto [h, w] : src) {
                dist[h][w] = 0;
                que.push({h, w});
            }
            while (!que.empty()) {
                auto [h, w] = que.front();
                que.pop();
                for (auto [dh, dw] : dir4) {
                    int nh = h + dh * k;
                    int nw = w + dw * k;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (grid[nh][nw] == invalid) continue;
                    if (acc.query(min(h, nh), min(w, nw), max(h, nh) + 1, max(w, nw) + 1) > 0) continue;
                    if (dist[nh][nw] == INF) {
                        dist[nh][nw] = dist[h][w] + 1;
                        que.push({nh, nw});
                    }
                }
            }
        };
        bfs({{sh, sw}});

        ll res = INF;
        ll mh = sh % k;
        ll mw = sw % k;
        rep(h, mh, H, k) {
            rep(w, mw, W, k) {
                if (grid[h][w] == 'G') {
                    chmin(res, dist[h][w]);
                }
                // 状態戻し
                dist[h][w] = INF;
            }
        }
        if (res >= INF) res = -1;
        print(res);
    }
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
