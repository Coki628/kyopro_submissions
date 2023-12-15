/*
・気まぐれ埋め
・きっちり自力AC！
・グリッド、最短経路2回
・フロー、最小費用流、点素パス、頂点コスト
・経路の往復をフローで解決する話は蟻本に載ってる。(P.214)
　今回は2回目通れない訳ではないが利得が0なのでそういう辺を張ればいい。
　久々だけど、頂点コストでin-out辺張る。利得なので下駄履かせる。
　今回の設定だと踏むマスの合計が一定なので、適切に差し引きができる。
　(これ一定じゃない時、うまく下駄履かす方法あるんだろうか。)
・ちなみに公式解はなんかすごい賢い3乗DPをしていた…。
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

#include "acl/mincostflow.hpp"

void solve() {
    ll H, W;
    cin >> H;
    H++;
    W = H;
    auto grid = listnd(H, W, 0LL);
    rep(h, H) {
        rep(w, W) {
            cin >> grid[h][w];
        }
    }

    ll MX = 1e5;
    ll N = H * W;
    atcoder::mcf_graph<ll, ll> mcf(N * 2 + 2);
    ll s = N * 2;
    ll t = N * 2 + 1;
    rep(h, H) {
        rep(w, W) {
            ll u = gridtoid(h, w, W);
            // 1回目に通る時
            mcf.add_edge(u, N + u, 1, MX - grid[h][w]);
            // 2回目に通るなら利得0のこっち
            mcf.add_edge(u, N + u, 1, MX);
            if (h + 1 < H) {
                ll v = gridtoid(h + 1, w, W);
                mcf.add_edge(N + u, v, 2, 0);
            }
            if (w + 1 < W) {
                ll v = gridtoid(h, w + 1, W);
                mcf.add_edge(N + u, v, 2, 0);
            }
        }
    }
    mcf.add_edge(s, 0, 2, 0);
    mcf.add_edge(N + gridtoid(H - 1, W - 1, W), t, 2, 0);
    auto [cap, cost] = mcf.flow(s, t);
    assert(cap == 2);
    ll ans = MX * (H + W - 1) * 2 - cost;
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
