/*
・きっちり自力AC！
・UF、サイクル判定
・各頂点に高々2本の辺があるグラフ。ありえない入力はないようなので、
　実は色とか気にしないで連結させて、サイクル判定すればOK。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    UnionFind uf(N);
    rep(i, M) {
        ll u, v;
        char c1, c2;
        cin >> u >> c1 >> v >> c2;
        u--, v--;
        uf.merge(u, v);
    }

    pll ans;
    for (auto r : uf.get_roots()) {
        if (uf.is_tree(r)) {
            ans.second++;
        } else {
            ans.first++;
        }
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
