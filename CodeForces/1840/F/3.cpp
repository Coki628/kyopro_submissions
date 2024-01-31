/*
参考：https://codeforces.com/contest/1840/submission/208790696
・多くの人が取ったと思われる方針。実装はくでさんのを参考に。
・座圧、グリッドBFS
・次のビームまでに到達できる場所だけ有効とするようなBFSをR回やる。
　なんだけど、普通に実装したら「ゴールしたけどちょうど次のビームが来る直前」
　みたいなケースが本当は到達してるのにビームにやられたことになってたりで、
　細部詰めるのに結局再度くでさんの実装見直したりで、
　こっちの方針が見えたとして自力で通せたかどうかは分からない。
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

void solve() {
    ll H, W;
    cin >> H >> W;
    ll R;
    cin >> R;
    Compress<ll> cp;
    vector<array<ll, 3>> qs;
    rep(i, R) {
        ll t, d, p;
        cin >> t >> d >> p;
        cp.add(t);
        qs.pb({t, d, p});
    }
    cp.add(0);
    cp.add(INF);
    cp.build();
    ll M = cp.size();
    vvpll adj(M);
    for (auto [t, d, p] : qs) {
        adj[cp[t]].eb(d, p);
    }

    auto dp = listnd(H + 1, W + 1, INF);
    dp[0][0] = 0;
    ll ans = INF;
    rep(i, M - 1) {
        ll t1 = cp.unzip(i);
        ll t2 = cp.unzip(i + 1);
        ll len = t2 - t1;
        auto bfs = [&](const vvl &cur) {
            auto res = list2d(H + 1, W + 1, INF);
            queue<pii> que;
            rep(h, H + 1) {
                rep(w, W + 1) {
                    if (cur[h][w] < INF) {
                        res[h][w] = 0;
                        que.push({h, w});
                    }
                }
            }
            while (!que.empty()) {
                auto [h, w] = que.front();
                que.pop();
                for (auto [dh, dw] : vector<pii>{{1, 0}, {0, 1}}) { // 2方向
                    int nh = h + dh;
                    int nw = w + dw;
                    if (nh < 0 or nw < 0 or nh > H or nw > W) continue;
                    if (res[nh][nw] == INF) {
                        res[nh][nw] = res[h][w] + 1;
                        que.push({nh, nw});
                    }
                }
            }
            // 次のビーム前にゴールに到達
            if (res[H][W] < len) {
                chmin(ans, t1 + res[H][W]);
            }
            // 次のビームまでに到達できないものは無効
            rep(h, H + 1) {
                rep(w, W + 1) {
                    if (res[h][w] > len) {
                        res[h][w] = INF;
                    }
                }
            }
            // 次のビームと重なる場所は無効
            for (auto [d, p] : adj[i + 1]) {
                if (d == 1) {
                    rep(w, W + 1) {
                        res[p][w] = INF;
                    }
                } else {
                    rep(h, H + 1) {
                        res[h][p] = INF;
                    }
                }
            }
            return res;
        };
        dp = bfs(dp);
    }
    if (ans >= INF) ans = -1;
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
