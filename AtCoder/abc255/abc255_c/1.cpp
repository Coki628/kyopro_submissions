/*
・自力AC。。
・等差数列、二分探索
・等差数列の0～N項でにぶたんする。INFが10^18だと足りなくてWA…。
　オーバーフローかと思ってint128使ってみたけど、こっちは要らなかった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

// constexpr long long INF = 1e18;
constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll x, a, d, N;
    cin >> x >> a >> d >> N;

    if (d == 0) {
        print(abs(x-a));
        return;
    }

    ll s = a;
    ll t = a + d * (N-1);
    assert(modulo(s, d) == modulo(t, d));
    if (s > t) {
        swap(s, t);
        d = -d;
    }

    ll res = bisearch_min(-1, N-1, [&](ll m) {
        return s+d*m >= x;
    });
    ll ans = INF;
    chmin(ans, abs(x-(s+d*res)));
    if (res > 0) {
        chmin(ans, abs(x-(s+d*(res-1))));
    }
    if (res < N-1) {
        chmin(ans, abs(x-(s+d*(res+1))));
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
