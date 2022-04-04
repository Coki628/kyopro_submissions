/*
・きっちり自力AC。
・最短経路に帰着、BFS
・ぱっと見、グラフっぽい。で、手元でちょっと試してみると、
　最短経路と一致しそうだね、となる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "graph/bfs.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        nodes[a].eb(b);
        nodes[b].eb(a);
    }

    auto res = bfs(nodes, {0});
    rep(i, N) {
        chmin(res[i], 120LL);
        print(res[i]);
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
