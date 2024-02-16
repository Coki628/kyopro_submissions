/*
ライブラリ整備：二重頂点連結成分分解、Block Cut Tree
・BCT構築して、HLDに突っ込んでパスクエリに対応する。
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

#include "graph/HeavyLightDecomposition.hpp"
#include "graph/BlockCutTree.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    BlockCutTree bct(nodes);
    ll N2 = bct.size();
    HeavyLightDecomposition hld(bct.aux);
    Accumulate<ll> acc(N2);
    rep(u, N2) {
        if (bct.is_articulation(u)) {
            acc.set(hld[u], 1);
        }
    }
    acc.build();
    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;
        x--, y--;

        x = bct.id(x), y = bct.id(y);
        ll res = hld.query(
            x,
            y,
            0LL,
            [&](ll a, ll b) { return acc.query(a, b); },
            [](ll a, ll b) { return a + b; }
        );
        if (bct.is_articulation(x)) res--;
        if (x != y and bct.is_articulation(y)) res--;
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
