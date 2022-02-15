/*
参考：https://twitter.com/shojin_pro/status/1493263897360359426
・結局自力は無理だったかな。。
・実装、上書きには逆操作、グリッド、BFSに帰着、8方向BFS、多点スタートBFS
・まず、上書きは逆操作にすると都合が良くなるテクを使う。まあこれはやった。
　逆操作で見ると、先に確定した所はもう何置いてもいいみたいになる。
・で、4マス1セットにした一回り小さいグリッドを見て、
　塗れる状態になった所から塗っていく。ここまでは自分でやった。
・ここでグリッドの状態の更新操作にsetでlogとか乗せちゃってTLEになったけど、
　shojinさんのツイートから、8方向BFSにできると聞く。
　そういう目で見ると、方針が立った。
・set使ったやつは、予め全状態をキューに詰めといて動的に更新みたいな感じで効率が悪かった。
　8方向チェックして、OKな状態になった段階でキューに詰めれば、普通にBFSにできた。
・それでも100万の内側で8方向と、さらにその中で4方向とか回すのでまあ重い。AC1.31秒。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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

#include "grid/constants/dir8.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vvl grid(H);
    rep(i, H) {
        grid[i] = LIST(W);
    }

    // 右上が(h,w)な4マスが今塗れる状態かどうか
    auto check = [&](ll h, ll w) -> bool {
        vector<ll> V;
        rep(nh, h, h+2) {
            rep(nw, w, w+2) {
                V.eb(grid[nh][nw]);
            }
        }
        UNIQUE(V);
        if (V[0] == -1) {
            V.erase(V.begin());
        }
        // 自由色分を除いて1色になっていればOK
        return V.size() == 1;
    };
    // 右上が(h,w)な4マスを塗る(自由マスとする)。新規で塗ったマスの数を返す
    auto paint = [&](ll h, ll w) -> ll {
        ll res = 0;
        rep(nh, h, h+2) {
            rep(nw, w, w+2) {
                if (grid[nh][nw] != -1) {
                    grid[nh][nw] = -1;
                    res++;
                }
            }
        }
        return res;
    };
    // ここに含まれる色を返す
    auto color = [&](ll h, ll w) -> ll {
        rep(nh, h, h+2) {
            rep(nw, w, w+2) {
                if (grid[nh][nw] != -1) {
                    return grid[nh][nw];
                }
            }
        }
        return -1;
    };

    queue<pll> que;
    ll N = (H-1)*(W-1);
    rep(h, H-1) {
        rep(w, W-1) {
            if (check(h, w)) {
                que.push({h, w});
            }
        }
    }
    // 塗り終えたマスの数
    ll donecnt = 0;
    vector<array<ll, 3>> ans;
    while (que.size() and donecnt < H*W) {
        // 4マス揃ってる方から優先して使う
        auto [h, w] = que.front(); que.pop();
        // 今回塗る色
        ll c = color(h, w);
        if (c == -1) continue;
        donecnt += paint(h, w);
        ans.pb({h+1, w+1, c});
        // 周囲8方向の確認
        for (auto [dh, dw] : dir8) {
            ll nh = h+dh, nw = w+dw;
            if (nh < 0 or nw < 0 or nh >= H-1 or nw >= W-1) continue;
            if (color(nh, nw) == -1) continue;
            if (check(nh, nw)) {
                que.push({nh, nw});
            }
        }
    }

    if (donecnt < H*W) {
        print(-1);
        return;
    }
    reverse(ALL(ans));
    print(ans.size());
    for (auto& arr : ans) print(arr);
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
