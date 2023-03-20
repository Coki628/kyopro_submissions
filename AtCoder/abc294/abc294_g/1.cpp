/*
・きっちり自力AC！
・HLD、BIT、辺属性
・辺属性のHLD久々で、もたついたのがもったいない。
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

#include "graph/HeavyLightDecomposition.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    vector<tuple<ll, ll, ll>> edges;
    rep(i, N - 1) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        edges.eb(u, v, c);
    }
    HeavyLightDecomposition hld(nodes);

    BIT<ll> bit(N);
    ll u, v, c;
    for (auto t : edges) {
        tie(u, v, c) = t;
        if (hld.dep[u] < hld.dep[v]) {
            bit.add(hld.in[v], c);
        } else {
            bit.add(hld.in[u], c);
        }
    }

    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll i, w;
            cin >> i >> w;
            i--;
            tie(u, v, c) = edges[i];
            if (hld.dep[u] < hld.dep[v]) {
                bit.update(hld.in[v], w);
            } else {
                bit.update(hld.in[u], w);
            }
        } else {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            ll res = hld.query(
                u, v, 0LL, [&](ll a, ll b) { return bit.query(a, b); },
                [](ll a, ll b) { return a + b; }, true
            );
            print(res);
        }
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
