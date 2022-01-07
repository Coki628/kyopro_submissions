/*
・abc218_f
・きっちり自力AC！
・BFS、最短経路
・これはまあ解法覚えてたしな。本番通せて嬉しかったからな。
　考察はその時に色々書いたやつを参照。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/graph/bfs.hpp"

void solve() {
    int N, M;
    cin >> N >> M;
    vvi nodes(N), nodesrev(N);
    vector<pii> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodesrev[v].eb(u);
        edges.eb(u, v);
    }

    auto dist = bfs(nodes, {0});
    auto distrev = bfs(nodesrev, {N-1});
    vector<ll> ans(M);
    rep(i, M) {
        auto [u, v] = edges[i];
        if (dist[N-1] < dist[u]+distrev[v]+1) {
            ans[i] = dist[N-1];
        } else {
            nodes[u].erase(find(ALL(nodes[u]), v));
            ans[i] = bfs(nodes, {0})[N-1];
            nodes[u].eb(v);
        }
        if (ans[i] >= INF) ans[i] = -1;
    }
    for (ll a : ans) print(a);
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
