/*
・惜しくも自力ならず。。悔しい。
・木グラフ、HLD
・HLDで任意の距離を高速に取れるようにしておく。
　その後DFSして、必要な頂点に来たら移動、距離がD超離れたら他方も近づける、
　って貪欲にやった。本番中WAだったけど、これはans += need;する所が
　need -= dl;より前になってしまっていたからで、それだけ直したら無事AC。。
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
    ll N, D;
    cin >> N >> D;
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    HeavyLightDecomposition hld(nodes);
    ll m1, m2;
    vector<ll> A(N), B(N);
    cin >> m1;
    rep(i, m1) {
        ll a;
        cin >> a;
        a--;
        A[a] = 1;
    }
    cin >> m2;
    rep(i, m2) {
        ll b;
        cin >> b;
        b--;
        B[b] = 1;
    }

    ll ans = 0;
    ll cura = 0, curb = 0;
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) {
                continue;
            }
            f(f, v, u);
        }
        if (A[u]) {
            ll da = hld.dist(cura, u);
            ans += da;
            cura = u;
            ll db = hld.dist(curb, u);
            if (db > D) {
                ll need = db - D;
                ans += need;
                ll lca = hld.lca(curb, u);
                ll dl = hld.dist(curb, lca);
                if (dl >= need) {
                    curb = hld.la(curb, need);
                } else {
                    need -= dl;
                    curb = hld.la(u, hld.dist(lca, u) - need);
                }
            }
        }
        if (B[u]) {
            ll db = hld.dist(curb, u);
            ans += db;
            curb = u;
            ll da = hld.dist(cura, u);
            if (da > D) {
                ll need = da - D;
                ans += need;
                ll lca = hld.lca(cura, u);
                ll dl = hld.dist(cura, lca);
                if (dl >= need) {
                    cura = hld.la(cura, need);
                } else {
                    need -= dl;
                    cura = hld.la(u, hld.dist(lca, u) - need);
                }
            }
        }
    };
    dfs(dfs, 0, -1);
    ans += hld.dist(cura, 0);
    ans += hld.dist(curb, 0);
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
