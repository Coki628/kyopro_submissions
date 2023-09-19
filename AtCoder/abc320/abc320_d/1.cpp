/*
・きっちり自力AC！
・座標平面
・XY独立、重み付きUF
・重み付きUFをxとyで2つ作る。
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

#include "graph/WeightedUnionFind.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    WeightedUnionFind<ll> wufx(N), wufy(N);
    rep(i, M) {
        ll a, b, x, y;
        cin >> a >> b >> x >> y;
        a--, b--;
        wufx.merge(a, b, x);
        wufy.merge(a, b, y);
    }

    print(mkp(0, 0));
    rep(i, 1, N) {
        if (wufx.same(0, i)) {
            ll x = wufx.diff(0, i);
            ll y = wufy.diff(0, i);
            print(mkp(x, y));
        } else {
            print("undecidable");
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
