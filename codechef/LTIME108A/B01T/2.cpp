/*
・自力AC！
・HLD、部分木クエリ、DFS
・貪欲に根に近い方から、大きく操作できる所からやる感じで通った。(未証明…)
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "graph/HeavyLightDecomposition.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    rep(i, N) {
        if (A[i] == 0) {
            A[i] = -1;
        }
    }
    ll need = sum(A);
    if (need < 0) {
        need = -need;
        rep(i, N) {
            A[i] = -A[i];
        }
    }
    vector<ll> ans;
    HeavyLightDecomposition hld(nodes);
    Accumulate<ll> acc(N);
    rep(u, N) {
        acc.set(hld.in[u], A[u]);
    }
    acc.build();
    ll cur = 0;
    auto dfs = [&](auto&& f, ll u, ll prv) {
        ll sm = acc.query(hld.in[u], hld.out[u])*2;
        if (sm > 0 and cur+sm <= need) {
            cur += sm;
            ans.eb(u+1);
            return;
        }
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
        }
    };
    dfs(dfs, 0, -1);

    print(ans.size());
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
