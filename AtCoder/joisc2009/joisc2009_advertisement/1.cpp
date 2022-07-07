/*
・JOI埋め
・これは自力WA。無向グラフかと思ってUFしてサンプル合わずで、
　じゃあ伝播しなくて直接知ってる人にしか伝わらないのかな、と思って
　隣接した頂点にだけ伝わる体で、その時点で隣接した頂点が多い方から優先みたいな
　適当な貪欲を投げると、サンプル合ってるけど全ケースWA。。
　結局無向グラフだと思ってる時点でスタートラインに立ててない…。
　連絡先…まあ有向グラフになるかぁ。。
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

#include "mystl/my_set.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    
    my_set<pll> se;
    vector<ll> sz(N);
    rep(u, N) {
        se.insert({nodes[u].size(), u});
        sz[u] = nodes[u].size();
    }
    vector<bool> removed(N);
    ll ans = 0;
    while (se.size()) {
        auto [_, u] = se.pop_back();
        if (removed[u]) continue;
        removed[u] = true;
        for (auto v : nodes[u]) {
            if (removed[v]) continue;
            removed[v] = true;
            for (auto w : nodes[v]) {
                if (removed[w]) continue;
                se.erase({sz[w], w});
                sz[w]--;
                se.insert({sz[w], w});
            }
        }
        ans++;
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
