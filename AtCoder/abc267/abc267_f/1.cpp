/*
・終了後自力AC？TLでキーワードは拾ってしまってたけど、これはちゃんと見ればノーヒントいけた気がする…。
・全方位木DP、HLD、LCA
・重みなしグラフなので、頂点uから距離k以上の頂点が存在するなら、そのパス上にkちょうども必ずある。
　よって全頂点で最遠点までの距離とその最遠な頂点が分かれば、
　パスを辿るのはLCA使って高速にできるので、任意のクエリに対応できそう。
　最遠点は木DPが全方位に乗るので、これに復元の時みたいにペアで番号も持たせればいけそう。
　で、実際いけたので、後はHLDにLCAと途中まで遡るやつも搭載されてるので、これもやる。
　各クエリ時に、そもそも最遠点でも足りない、LCAより前か先、で場合分け。
・まじでこれはE詰まってなければいけたんじゃないかなー、もったいない…。
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

#include "graph/ReRooting.hpp"
#include "graph/HeavyLightDecomposition.hpp"

auto f1 = [](pii a, pii b) -> pii {
    if (a.first >= b.first) {
        return a;
    } else {
        return b;
    }
};
auto f2 = [](pii a, int v) -> pii {
    if (a.first == 0) {
        return {1, v};
    } else {
        return {a.first+1, a.second};
    }
};
// if (chmax(dp[u], dp[v]+1)) {
//     mxv[u] = mxv[v];
// }

void solve() {
    ll N;
    cin >> N;
    auto rr = get_rerooting(N, f1, f2, pii{0, -1}, 0);
    vvi nodes(N);
    rep(i, N-1) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        rr.add_edge_bi(a, b, b, a);
        nodes[a].eb(b);
        nodes[b].eb(a);
    }
    auto res = rr.build();

    HeavyLightDecomposition hld(nodes);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll u, k;
        cin >> u >> k;
        u--;

        if (res[u].first < k) {
            print(-1);
        } else {
            // uから一番遠い頂点v
            ll v = res[u].second;
            ll lca = hld.lca(u, v);
            ll dist1 = hld.dist(u, lca);
            if (k <= dist1) {
                // u -> lca
                ll w = hld.la(u, k);
                print(w+1);
            } else {
                k -= dist1;
                ll dist2 = hld.dist(v, lca);
                // lca -> v
                ll w = hld.la(v, dist2-k);
                print(w+1);
            }
        }
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
