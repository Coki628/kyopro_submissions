/*
・きっちり自力AC！
・BFS
・グラフ2つ作ってそれぞれBFSして最大距離+1。
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
    int N1, N2, M;
    cin >> N1 >> N2 >> M;
    vvi nodes1(N1), nodes2(N2);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        if (u < N1) {
            nodes1[u].eb(v);
            nodes1[v].eb(u);
        } else {
            u -= N1, v -= N1;
            nodes2[u].eb(v);
            nodes2[v].eb(u);
        }
    }

    auto dist1 = bfs(nodes1, {0});
    auto dist2 = bfs(nodes2, {N2 - 1});
    ll ans = max(dist1) + max(dist2) + 1;
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
