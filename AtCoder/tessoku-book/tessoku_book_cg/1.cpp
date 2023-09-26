/*
・2次元累積和
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

#include "datastructure/Accumulate2D.hpp"

void solve() {
    ll M = 1500;
    Accumulate2D<ll> acc(M + 1, M + 1);
    ll N;
    cin >> N;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        acc.add(x, y, 1);
    }
    acc.build();

    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        ll res = acc.query(a, b, c + 1, d + 1);
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
