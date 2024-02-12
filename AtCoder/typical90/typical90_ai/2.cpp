/*
ライブラリ整備：Auxiliary Tree
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

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    AuxiliaryTree aux(nodes);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll k;
        cin >> k;
        vector<int> vec(k);
        cin >> vec;
        vec--;
        auto r = aux.build(vec);
        ll res = 0;
        auto dfs = [&](auto dfs, ll u, ll prv) -> void {
            for (auto v : aux[u]) {
                if (v == prv) continue;
                dfs(dfs, v, u);
                res += aux.dist(v, u);
            }
        };
        dfs(dfs, r, -1);
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
