/*
・きっちり自力AC！
・一見して、HLDとWMで殴ろう、ってなった。
　実際にはKが20しかないので、もっと適当な方針で通るそう。
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
#include "template.hpp"

#include "graph/HeavyLightDecomposition.hpp"
#include "segment/WaveletMatrix.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    HeavyLightDecomposition hld(nodes);
    vector<ll> tmp(N);
    rep(i, N) {
        tmp[hld.in[i]] = A[i];
    }
    WaveletMatrix<ll, 33> wm(tmp);
    rep(i, Q) {
        ll v, k;
        cin >> v >> k;
        v--; k--;
        ll res = wm.kth_largest(hld.in[v], hld.out[v], k);
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
