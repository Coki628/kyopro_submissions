/*
・きっちり自力AC！
・最短経路、BFS、中継地全探索
・中継地の候補Kは最大20。毎クエリ全中継地をチェックできる。
　ので前計算BFSで全中継地からの最短路を求めておく。
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
    int N, M, Q, K;
    cin >> N >> M >> Q >> K;
    auto A = LIST<int>(K);
    rep(i, K) A[i]--;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vvl dist(K);
    rep(i, K) {
        dist[i] = bfs(nodes, {A[i]});
    }
    rep(i, Q) {
        ll s, t;
        cin >> s >> t;
        s--; t--;
        ll res = INF;
        rep(i, K) {
            chmin(res, dist[i][s]+dist[i][t]);
        }
        print(res);
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
