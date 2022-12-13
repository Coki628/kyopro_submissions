/*
参考：https://atcoder.jp/contests/past202206-open/editorial/4061
・状態増やしてBFS
・自分の位置と荷物の位置を両方添字にして4次元DPにする。
　確かにこれだと全然楽だ。制約小さい時はこういう方針も見えないとダメだなー…。
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

    pll a, s, g;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == 'a') {
                a = {h, w};
            } else if (grid[h][w] == 's') {
                s = {h, w};
            } else if (grid[h][w] == 'g') {
                g = {h, w};
            }
        }
    }

    auto dp = listnd(H, W, H, W, -1);
    using P = tuple<ll, ll, ll, ll>;
    queue<P> que;
    auto [sh, sw] = s;
    auto [ah, aw] = a;
    auto [gh, gw] = g;
    dp[sh][sw][ah][aw] = 0;
    que.push({sh, sw, ah, aw});
    while (que.size()) {
        auto [ch, cw, ah, aw] = que.front();
        que.pop();
        for (auto [dh, dw] : dir4) {
            ll nh = ch + dh;
            ll nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) {
                continue;
            }
            if (grid[nh][nw] == '#') {
                continue;
            }
            // 荷物を押す時
            if (nh == ah and nw == aw) {
                ll anh = ah + dh;
                ll anw = aw + dw;
                if (anh < 0 or anw < 0 or anh >= H or anw >= W) {
                    continue;
                }
                if (grid[anh][anw] == '#') {
                    continue;
                }
                if (dp[nh][nw][anh][anw] == -1) {
                    dp[nh][nw][anh][anw] = dp[ch][cw][ah][aw] + 1;
                    que.push({nh, nw, anh, anw});
                }
            } else {
                if (dp[nh][nw][ah][aw] == -1) {
                    dp[nh][nw][ah][aw] = dp[ch][cw][ah][aw] + 1;
                    que.push({nh, nw, ah, aw});
                }
            }
        }
    }
    int ans = MOD;
    rep(ch, H) {
        rep(cw, W) {
            if (dp[ch][cw][gh][gw] != -1) {
                chmin(ans, dp[ch][cw][gh][gw]);
            }
        }
    }
    if (ans == MOD) {
        ans = -1;
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
