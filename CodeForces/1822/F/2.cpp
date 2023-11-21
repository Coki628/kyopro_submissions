/*
・木の直径、最遠点取得
・なんかいつも全方位でやっちゃってたけど、
　木の最遠点は直径から取れると言うのがあるので、やる。
　あんま使わないけど、なんだかんだ通算だと結構見てる気がするので、
　木の直径ライブラリ化しておいた。
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

#include "graph/get_diameter.hpp"
#include "graph/bfs.hpp"

void solve() {
    ll N, K, C;
    cin >> N >> K >> C;
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto [_, u, v] = get_diameter(nodes);
    auto dist1 = bfs(nodes, {u});
    auto dist2 = bfs(nodes, {v});
    auto dist3 = bfs(nodes, {0});
    ll ans = -INF;
    rep(i, N) {
        chmax(ans, max(dist1[i], dist2[i]) * K - dist3[i] * C);
    }
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
