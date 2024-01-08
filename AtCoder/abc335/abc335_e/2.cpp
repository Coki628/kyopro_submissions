/*
・こっちのが正攻法っぽい方針。
・DAGのDP、SCC、グラフの縮約
・ついこの前作った縮約付きSCCライブラリ早速使えたじゃん…。
　これを思いつけないとは、、、悲しい。
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

#include "graph/SCC.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    cin >> A;
    SCC scc(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        if (A[u] < A[v]) {
            scc.add_edge(u, v);
        } else if (A[u] > A[v]) {
            scc.add_edge(v, u);
        } else {
            scc.add_edge(u, v);
            scc.add_edge(v, u);
        }
    }

    scc.build();
    scc.construct();
    ll N2 = scc.size();
    vvi nodes2(N2);
    for (auto [u, v] : scc.get_edges2()) {
        if (u == v) continue;
        nodes2[u].eb(v);
    }
    vector<ll> dp(N2, -INF);
    dp[scc.NtoN2[0]] = 1;
    rep(u, N2) {
        if (dp[u] <= -INF) continue;
        for (auto v : nodes2[u]) {
            chmax(dp[v], dp[u] + 1);
        }
    }
    ll ans = dp[scc.NtoN2[N - 1]];
    if (ans <= -INF) ans = 0;
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
