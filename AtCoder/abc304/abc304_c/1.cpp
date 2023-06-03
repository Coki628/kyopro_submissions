/*
・きっちり自力AC！
・UF、ユークリッド距離
・距離判定、今回は真面目に整数のままでやった。
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

#include "geometry/Point.hpp"

void solve() {
    ll N, D;
    cin >> N >> D;
    vector<Point<ll>> XY;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        XY.pb({x, y});
    }

    UnionFind uf(N);
    ll D2 = D * D;
    rep(i, N) {
        rep(j, i + 1, N) {
            if (XY[i].abs2(XY[j]) <= D2) {
                uf.merge(i, j);
            }
        }
    }
    rep(i, N) {
        if (uf.same(0, i)) {
            Yes();
        } else {
            No();
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
