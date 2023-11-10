/*
・木グラフ、DFS、木DP
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

void solve() {
    ll N, t;
    cin >> N >> t;
    t--;
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<ll> dp(N, 0LL);
    auto dfs = [&](auto&& f, int u, int prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            chmax(dp[u], dp[v] + 1);
        }
    };
    dfs(dfs, t, -1);
    print(dp);
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
