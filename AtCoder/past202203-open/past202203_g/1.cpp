/*
・きっちり自力AC。
・二分探索
・実数にぶたんする。
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

#include "common/bisearch_real.hpp"

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;

    // rep(i, 11, 20) {
    //     ld x = i/(ld)10;
    //     ld res = a*pow(x, 5) + b*x + c;
    //     print(res);
    // }
    ld res = bisearch_min(1, 2, [&](ld x) {
        return a*pow(x, 5) + b*x + c >= 0;
    }, 100);
    print(res);
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
