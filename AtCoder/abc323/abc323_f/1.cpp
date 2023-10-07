/*
・自力ならず。。悔しい。
・座標平面、座圧ダイクストラ、場合分け
・最初、地獄場合分けしかないと思ってガチャガチャやったけどやっぱりダメで、
　座圧して前半操作の最短路出せばいくらか楽になりそうと気付いたが、
　もうかなり終了近くになってしまっていたので時間切れ。終了後、色々整えて無事AC。
・前半パートで横に押す位置と縦に押す位置への最短路を求めておく。
　これで3点の関係だった問題が2点の関係だけになるので場合分けが大分楽になる。
　先に押した後、後に押す側をやる必要があるかに注意しつつ、
　どっち軸に先に押すか2パターンを試せばOK。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll xa, ya, xb, yb, xc, yc;
    cin >> xa >> ya >> xb >> yb >> xc >> yc;

    Compress<ll> cpx, cpy;
    cpx.add(xa);
    cpx.add(xb);
    cpx.add(xb - 1);
    cpx.add(xb + 1);
    cpx.add(xc);
    cpy.add(ya);
    cpy.add(yb);
    cpy.add(yb - 1);
    cpy.add(yb + 1);
    cpy.add(yc);
    cpx.build();
    cpy.build();

    ll tgtx = xb;
    if (xb < xc) {
        tgtx = xb - 1;
    } else if (xb > xc) {
        tgtx = xb + 1;
    }
    ll tgty = yb;
    if (yb < yc) {
        tgty = yb - 1;
    } else if (yb > yc) {
        tgty = yb + 1;
    }
    // 押すのを開始するまでの移動
    ll H = cpy.size(), W = cpx.size();
    auto res = listnd(H, W, INF);
    using P = tuple<ll, int, int>;
    priority_queue<P, vector<P>, greater<P>> que;
    que.push({0, cpy[ya], cpx[xa]});
    res[cpy[ya]][cpx[xa]] = 0;
    while (que.size()) {
        auto [dist, h, w] = que.top(); que.pop();
        if (res[h][w] < dist) continue;
        for (auto [dh, dw] : dir4) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (nh == cpy[yc] and nw == cpx[xc] or nh == cpy[yb] and nw == cpx[xb]) {
                continue;
            }
            ll cost = abs(cpy.unzip(h) - cpy.unzip(nh)) + abs(cpx.unzip(w) - cpx.unzip(nw));
            if (chmin(res[nh][nw], dist + cost)) {
                que.push({dist + cost, nh, nw});
            }
        }
    }
    // 横を先にやる
    ll ans1 = res[cpy[yb]][cpx[tgtx]];
    if (ans1 < INF) {
        ans1 += abs(xb - xc);
        if (yb != yc) {
            ans1 += abs(yb - yc) + 2;
        }
    }
    // 縦を先にやる
    ll ans2 = res[cpy[tgty]][cpx[xb]];
    if (ans2 < INF) {
        ans2 += abs(yb - yc);
        if (xb != xc) {
            ans2 += abs(xb - xc) + 2;
        }
    }
    ll ans = min(ans1, ans2);
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
