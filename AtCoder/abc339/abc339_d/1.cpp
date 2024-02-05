/*
・なんとか自力AC！これは危なかった。
・状態増やしてグリッドBFS
・なぜかなかなか見えなかったんだけど、
　2人の位置両方を状態として持てば、
　後は普通にグリッドBFSやってく感じになる。
　微妙に小さい制約がもっと愚直な全探索解法を連想させるのとか、
　「2人が同じ方向に連動して動く」っていう問題設定が
　なんとなく、都合の良い特殊な性質あるのを疑ってしまうのとか、
　そういう所で惑わされるんだと思う。
　事実、今回これ水diffまで乗ってるので、みんな苦戦してたと思う。
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
    ll H;
    cin >> H;
    ll W = H;
    vector<string> grid(H);
    cin >> grid;

    ll h1 = -1, w1 = -1, h2 = -1, w2 = -1;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == 'P') {
                if (h1 == -1) {
                    h1 = h, w1 = w;
                } else {
                    h2 = h, w2 = w;
                }
            }
        }
    }

    auto bfs = [&](char invalid = '#') {
        auto res = listnd(H, W, H, W, INF);
        queue<array<ll, 4>> que;
        res[h1][w1][h2][w2] = 0;
        que.push({h1, w1, h2, w2});
        while (!que.empty()) {
            auto [ha, wa, hb, wb] = que.front();
            que.pop();
            for (auto [dh, dw] : dir4) {
                int nha = clamp(ha + dh, 0LL, H - 1);
                int nwa = clamp(wa + dw, 0LL, W - 1);
                int nhb = clamp(hb + dh, 0LL, H - 1);
                int nwb = clamp(wb + dw, 0LL, W - 1);
                if (grid[nha][nwa] == invalid) {
                    nha = ha, nwa = wa;
                }
                if (grid[nhb][nwb] == invalid) {
                    nhb = hb, nwb = wb;
                }
                if (res[nha][nwa][nhb][nwb] == INF) {
                    res[nha][nwa][nhb][nwb] = res[ha][wa][hb][wb] + 1;
                    que.push({nha, nwa, nhb, nwb});
                }
            }
        }
        return res;
    };
    auto res = bfs();
    ll ans = INF;
    rep(h, H) {
        rep(w, W) {
            chmin(ans, res[h][w][h][w]);
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
