/*
・二部グラフ判定
・なんやかんや何回も使ってるので、ライブラリ化しておいた。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "graph/is_bipartite.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(M), B(M);
    cin >> A >> B;
    A--, B--;

    vvi nodes(N);
    rep(i, M) {
        ll u = A[i];
        ll v = B[i];
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    if (is_bipartite(nodes)) {
        Yes();
    } else {
        No();
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
