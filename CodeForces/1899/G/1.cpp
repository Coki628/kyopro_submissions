/*
・これは自力TLE。。
・Mo*HLD*区間加算BIT
・10万に√とlog2つはさすがに重すぎた。。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

#include "graph/HeavyLightDecomposition.hpp"
#include "datastructure/BIT2.hpp"
#include "datastructure/Mo.hpp"

void solve() {
    int N, Q;
    cin >> N >> Q;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    vector<int> P(N);
    cin >> P;
    P--;

    HeavyLightDecomposition hld(nodes);
    Mo mo(N);
    BIT2<int> bit(N);
    vector<int> X(Q);
    rep(i, Q) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, x--;
        mo.add(l, r);
        X[i] = x;
    }
    auto add = [&](int i) -> void {
        int u = P[i];
        hld.update(0, u, [&](int a, int b) { bit.add(a, b, 1); });
    };
    auto erase = [&](int i) -> void {
        int u = P[i];
        hld.update(0, u, [&](int a, int b) { bit.add(a, b, -1); });
    };
    vector<string> ans(Q);
    auto out = [&](int i) -> void {
        int u = X[i];
        if (bit[hld.in[u]] > 0) {
            ans[i] = "YES";
        } else {
            ans[i] = "NO";
        }
    };
    mo.build(add, erase, out);
    print(ans, '\n');
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
