/*
・自力ならず。方針が見えなかった。
・BFS、半分全列挙、両側探索
・久しぶりで気付けなかった。必要な回数の半分ずつだけ、終点と始点から探索するやつ。
　昔、本でオレは両側探索で覚えたけど、TLのみんなを見る限り、
　半分全列挙の一種として昨今は認識されてるようだ。
・グリッドの状態そのままmapに突っ込んでBFSするのとかは割と定形なので、
　部分グリッドの180度回転パートの添字合わせが一番時間かかった…。
　にしても、時間あればこれは本番でも通せそう。気付ければ。
　まあ体調あんま良くなかったとはいえ、考察で見えないんじゃ無理だけどね…。
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
    auto grid = listnd(H, W, 0);
    rep(h, H) {
        rep(w, W) {
            cin >> grid[h][w];
        }
    }

    auto rot180 = [](const vvi &grid, ll sh, ll sw, ll szh, ll szw) {
        auto res = grid;
        rep(i, szh * szw / 2) {
            auto [h, w] = idtogrid(i, szw);
            swap(res[sh + h][sw + w], res[sh + szh - h - 1][sw + szw - w - 1]);
        }
        return res;
    };
    vvi goal = listnd(H, W, 0);
    rep(h, H) {
        rep(w, W) {
            goal[h][w] = h * W + w + 1;
        }
    }
    map<vvi, ll> memo1, memo2;
    Deque<vvi> que1, que2;
    que1.pb(grid);
    que2.pb(goal);
    memo1[grid] = 0;
    memo2[goal] = 0;
    while (que1.size()) {
        auto cur = que1.pop_front();
        if (memo1[cur] == 10) continue;
        rep(h, 2) {
            rep(w, 2) {
                auto res = rot180(cur, h, w, H - 1, W - 1);
                if (not memo1.count(res)) {
                    memo1[res] = memo1[cur] + 1;
                    que1.pb(res);
                }
            }
        }
    }
    while (que2.size()) {
        auto cur = que2.pop_front();
        if (memo2[cur] == 10) continue;
        rep(h, 2) {
            rep(w, 2) {
                auto res = rot180(cur, h, w, H - 1, W - 1);
                if (not memo2.count(res)) {
                    memo2[res] = memo2[cur] + 1;
                    que2.pb(res);
                }
            }
        }
    }
    ll ans = INF;
    for (auto& [g, val1] : memo1) {
        if (memo2.count(g)) {
            ll val2 = memo2[g];
            chmin(ans, val1 + val2);
        }
    }
    if (ans >= INF) ans = -1;
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
