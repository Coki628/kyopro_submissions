/*
・木グラフ、転倒数、列挙
・寄与、オイラーツアー、部分木クエリ、range_freq、全方位木DP
・一応、全方位に乗せるのもやってみた。区間加算パートが要らなくなったけど、
　部分木へのrange_freqで寄与を集める所は結局同じ考察が必要。
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
#include "graph/ReRooting.hpp"
#include "datastructure/WaveletMatrix.hpp"

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
    
    HeavyLightDecomposition hld(nodes);
    WaveletMatrix<ll> wm(N);
    rep(u, N) {
        wm.set(hld[u], u);
    }
    wm.build();

    auto f1 = [](ll a, ll b) -> ll {
        return a + b;
    };
    auto f2 = [](ll a, ll x) -> ll {
        return a + x;
    };
    auto rr = get_rerooting(N, f1, f2, 0LL, 0LL);
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            // 頂点uと部分木側にあるx<uとなる(x,u)ペア
            ll vcnt1 = wm.range_freq(hld.in[v], hld.out[v], 0, u);
            // 頂点vと根側にあるx<vとなる(x,v)ペア
            ll vcnt2 = wm.range_freq(0, hld.in[v], 0, v) + wm.range_freq(hld.out[v], N, 0, v);
            rr.add_edge(u, v, vcnt1, vcnt2);
        }
    };
    dfs(dfs, 0, -1);

    vector<ll> res = rr.build();
    print(res);
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
