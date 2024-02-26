/*
・きっちり自力AC！
・木グラフ、頂点属性、パス数え上げ、Auxiliary Tree、木DP
・色毎に木DPする。(今見ている頂点,部分木)と部分木同士の2タイプを数える。
　今見ている頂点が色cならそこと部分木で数えて、以降ここが通れないので自身を1に、
　色cでないなら部分木同士が通れるのでそこでペアを数える。
　最近ライブラリ整備やってた成果が出た感じだ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "graph/AuxiliaryTree.hpp"

void solve(int testcase) {
    ll N;
    cin >> N;
    auto C = LIST(N);
    C--;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vvi adj(N);
    rep(i, N) {
        adj[C[i]].eb(i);
    }

    AuxiliaryTree aux(nodes);
    vector<ll> dp(N);
    ll ans = 0;
    rep(c, N) {
        if (adj[c].empty()) continue;
        auto r = aux.build(adj[c]);
        auto dfs = [&](auto &&f, ll u, ll prv) -> void {
            for (auto v : aux[u]) {
                if (v == prv) continue;
                f(f, v, u);
                if (C[u] != c) {
                    ans += dp[u] * dp[v];
                }
                dp[u] += dp[v];
            }
            if (C[u] == c) {
                ans += dp[u];
                dp[u] = 1;
            }
        };
        dfs(dfs, r, -1);
        for (auto u : aux.get_vertices()) {
            dp[u] = 0;
        }
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
    rep(t, T) solve(t);

    return 0;
}
