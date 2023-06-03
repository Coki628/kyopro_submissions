/*
・自力ならず。。これはマジで悔しい。
・UFで連結させた後、条件になる頂点の連結成分ペアをsetで持つ。
　なんでこのsetでペア持つの思いつかなかったんだろう…。
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
        cin >> u >> v;
        u--, v--;
        uf.merge(u, v);
    }

    ll K;
    cin >> K;
    set<pll> ng;
    rep(i, K) {
        ll x, y;
        cin >> x >> y;
        x--, y--;
        ng.insert({uf.find(x), uf.find(y)});
        ng.insert({uf.find(y), uf.find(x)});
    }
    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll p, q;
        cin >> p >> q;
        p--, q--;
        if (ng.count({uf.find(p), uf.find(q)})) {
            No();
        } else {
            Yes();
        }
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
