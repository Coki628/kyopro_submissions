/*
・自力AC！
・実験
・N=30くらいで実験すると、同値と2倍と3倍くらいしかなさそうなので、数える。
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
    ll N;
    cin >> N;

    // rep(a, 1, N+1) {
    //     rep(b, 1, N+1) {
    //         debug(a);
    //         debug(b);
    //         debug(lcm(a, b)/gcd(a, b));
    //         print();
    //     }
    // }

    ll ans = N + (N/2)*2 + (N/3)*2;
    print(ans);
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
