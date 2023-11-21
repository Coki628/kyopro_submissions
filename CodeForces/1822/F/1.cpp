/*
・きっちり自力AC！
・最遠点取得、全方位木DP
・本日中盤以降で手際良かったのここだけ。。
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

#include "graph/ReRooting.hpp"
#include "graph/bfs.hpp"

auto f1 = [](ll a, ll b) {
    return max(a, b);
};
auto f2 = [](ll a, ll c) {
    return a + c;
};

void solve() {
    ll N, K, C;
    cin >> N >> K >> C;
    auto rr = get_rerooting(N, f1, f2, 0LL, 0LL);
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        rr.add_edge(u, v, K);
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto res = rr.build();
    auto dist = bfs(nodes, {0});
    ll ans = -INF;
    rep(i, N) {
        chmax(ans, res[i] - dist[i] * C);
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
