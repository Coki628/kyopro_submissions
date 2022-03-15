/*
・dojo set_d_5_5
・さくっと自力AC！
・部分永続UF、二分探索
・部分永続UFがあるとクエリ毎にぶたんするだけみたいになる。
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

#include "graph/PartiallyPersistentUnionFind.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    PartiallyPersistentUnionFind uf(N);
    rep(t, 1, M+1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        uf.merge(t, u, v);
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll u, v;
        cin >> u >> v;
        u--; v--;

        ll res = bisearch_min(0, M+1, [&](ll m) {
            return uf.same(m, u, v);
        });
        if (res == M+1) res = -1;
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
