/*
参考：https://atcoder.jp/contests/abc257/editorial
・自力ならず。。グラフでこれは悔しい。
・最短経路、超頂点
・超頂点作るとこまではやったのになぁ…。その先が。。
・超頂点Nと頂点iの所を、中継地全探索の時みたいに0とN-1からのBFSで、
　通らない、どっち側から通る、の3通り調べて最短求めればいい。
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
    ll N, M;
    cin >> N >> M;
    vvi nodes(N+1);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        if (u == -1) u = N;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto dist1 = bfs(nodes, {0});
    auto dist2 = bfs(nodes, {(int)N-1});
    vector<ll> ans(N);
    rep(i, N) {
        ans[i] = min({
            dist1[N-1],
            dist1[i]+dist2[N],
            dist1[N]+dist2[i],
        });
        if (ans[i] >= INF) ans[i] = -1;
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
