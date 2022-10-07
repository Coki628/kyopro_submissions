/*
・速攻自力AC。
・ダイクストラ2回で中継地点全探索。これPASTでめっちゃ出てない？
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

#include "graph/_dijkstra.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpil nodes(N), revnodes(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        revnodes[v].eb(u, c);
    }

    auto res1 = dijkstra(nodes, 0);
    auto res2 = dijkstra(revnodes, N-1);
    rep(i, N) {
        if (res1[i] == INF or res2[i] == INF) {
            print(-1);
        } else {
            ll res = res1[i] + res2[i];
            print(res);
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
