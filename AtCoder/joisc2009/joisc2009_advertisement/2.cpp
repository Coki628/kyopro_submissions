/*
・JOI埋め
・自力ならず？誤読。。
・強連結成分分解
・有向グラフだと分かっていれば、解法生えたかもしれないのに…。
　SCCして、閉路潰したDAGでグラフ再構築して、入次数0の頂点数が答え。
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

#include "acl/scc.hpp"
using namespace atcoder;

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pii> edges;
    scc_graph scc(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        edges.eb(u, v);
        scc.add_edge(u, v);
    }

    auto groups = scc.scc();
    ll L = groups.size();
    vector<ll> grp(N);
    rep(i, L) {
        for (auto u : groups[i]) {
            grp[u] = i;
        }
    }
    vector<ll> in(L);
    for (auto [u, v] : edges) {
        if (grp[u] == grp[v]) continue;
        in[grp[v]]++;
    }
    ll ans = 0;
    rep(i, L) {
        if (in[i] == 0) ans++;
    }
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
