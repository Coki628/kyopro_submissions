/*
・きっちり自力AC！
・座圧、BFS
・座圧してBFSやるだけなんだけど、これもうCかぁってなるよね。
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

#include "graph/bfs.hpp"

void solve() {
    ll N;
    cin >> N;
    
    Compress<ll> cp;
    cp.add(1);
    vector<pll> edges;
    rep(i, N) {
        ll u, v;
        cin >> u >> v;
        edges.eb(u, v);
        cp.add(u);
        cp.add(v);
    }
    cp.build();
    ll L = cp.size();
    vvi nodes(L);
    rep(i, N) {
        ll u = cp[edges[i].first];
        ll v = cp[edges[i].second];
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto res = bfs(nodes, {0});
    ll ans = 1;
    rep(i, L) {
        if (res[i] < INF) {
            ans = cp.unzip(i);
        }
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
