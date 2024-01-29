/*
・これはWA。
・凸になるんじゃないかと予想してさぶたんしたけど嘘だった…。
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

#include "common/trisearch.hpp"
#include "graph/HeavyLightDecomposition.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    HeavyLightDecomposition hld(nodes);
    auto seg = get_segment_tree(N, [](ll a, ll b) { return a | b; }, 0LL);
    rep(u, N) {
        seg.set(hld[u], A[u]);
    }
    seg.build();

    ll Q;
    cin >> Q;
    vector<ll> ans(Q);
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;
        x--, y--;

        ll len = hld.dist(x, y);
        auto [id, val] = trisearch_max(0, len + 1, [&](ll m) {
            ll lca = hld.lca(x, y);
            ll d1 = hld.dist(x, lca);
            ll d2 = len - d1;
            ll z = m <= d1 ? hld.la(x, m) : hld.next(lca, y, m - d1);
            ll resa = hld.query(x, z, 0LL, [&](ll a, ll b) { return seg.query(a, b); }, [](ll a, ll b) { return a | b; });
            ll resb = hld.query(z, y, 0LL, [&](ll a, ll b) { return seg.query(a, b); }, [](ll a, ll b) { return a | b; });
            return popcount(resa) + popcount(resb);
        }, 300);
        ans[i] = val;
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
