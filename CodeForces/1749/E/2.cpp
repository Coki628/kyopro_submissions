/*
・終了30分後くらいでなんとか自力AC…？WAでテストケース覗いたけどまあ手がかり無かったしな。。
・グリッドBFS、01BFS、多点スタート、斜め移動、経路復元
・大変だったけど、終わってみればグリッドの典型要素詰め合わせだな…。
・上下を分断したいので、左端列から右端列までを♯でつなぐ最短パスを1個作ることを考える。
　左端列全部を始点として多点スタート、元々♯の所をコスト0として01BFS、
　遷移は斜め4方向、行きたいマスの上下左右に既に♯があると遷移不可、
　経路復元できるようにDP復元みたいに遷移元をペアに持たせておく。
　初手BFSじゃなくてDPでやろうとして沼ったのが失敗。
　元々の♯の位置によっては、ぐるっと回り込んだ方が最善の場合もあるんだよね…。
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

#include "grid/constants/dir_diagonals.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    rep(i, H) {
        cin >> grid[i];
    }

    auto res = listnd(H, W, pair<ll, pii>{INF, {-1, -1}});
    deque<pii> que;
    rep(h, H) {
        int w = 0;
        bool ok = true;
        for (auto [dh, dw] : dir4) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (grid[nh][nw] == '#') {
                ok = false;
                break;
            }
        }
        if (not ok) continue;
        if (grid[h][w] == '#') {
            que.push_front({h, 0});
            res[h][0] = {0, {INF, -1}};
        } else {
            que.pb({h, 0});
            res[h][0] = {1, {INF, -1}};
        }
    }
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop_front();
        for (auto [dh, dw] : dir_diagonals) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            bool ok = true;
            for (auto [dh2, dw2] : dir4) {
                int nh2 = nh + dh2;
                int nw2 = nw + dw2;
                if (nh2 < 0 or nw2 < 0 or nh2 >= H or nw2 >= W) continue;
                if (grid[nh2][nw2] == '#') {
                    ok = false;
                    break;
                }
            }
            if (not ok) continue;
            if (res[nh][nw].first == INF) {
                if (grid[nh][nw] == '#') {
                    res[nh][nw] = {res[h][w].first, {h, w}};
                    que.push_front({nh, nw});
                } else {
                    res[nh][nw] = {res[h][w].first + 1, {h, w}};
                    que.pb({nh, nw});
                }
            }
        }
    }

    ll mn = INF;
    vector<pll> vec;
    rep(h, H) {
        if (chmin(mn, res[h][W-1].first)) {
            vec.clear();
            ll curh = h, curw = W-1;
            while (curw >= 0) {
                vec.eb(curh, curw);
                tie(curh, curw) = res[curh][curw].second;
            }
        }
    }
    if (mn < INF) {
        vector<string> ans = grid;
        for (auto [h, w] : vec) {
            ans[h][w] = '#';
        }
        YES();
        print(ans, '\n');
    } else {
        NO();
    }
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
