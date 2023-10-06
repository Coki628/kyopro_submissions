/*
・きっちり自力AC！
・順列、倍数
・ベン図、包除、LCM、等差数列の和
・indexでxの倍数が+に、yの倍数が-に寄与して両方の倍数は相殺される。
　それぞれ寄与できる箇所の数を出して、大きい方と小さい方をできるだけ与える。
　順列の最大の和と最小の和なので公差1,-1の等差数列の和で求まる。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "numbers/arithmetic_sequence_sum.hpp"

void solve() {
    ll n, x, y;
    cin >> n >> x >> y;

    ll xcnt = n / x;
    ll ycnt = n / y;
    ll xycnt = n / lcm(x, y);
    xcnt -= xycnt;
    ycnt -= xycnt;
    assert(xcnt + ycnt <= n);
    ll xsm = arithmetic_sequence_sum(n, -1LL, xcnt);
    ll ysm = arithmetic_sequence_sum(1LL, 1LL, ycnt);
    ll ans = xsm - ysm;
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
