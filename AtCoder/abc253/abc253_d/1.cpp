/*
・きっちり自力AC！
・等差数列の和、包除原理
・全体とaとbとlcmで等差数列の和4回取って包除。
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

#include "numbers/arithmetic_sequence_sum.hpp"

void solve() {
    ll N, a, b;
    cin >> N >> a >> b;

    ll l = lcm(a, b);
    ll total = arithmetic_sequence_sum(1LL, 1LL, N);
    ll acnt = N / a;
    ll asum = arithmetic_sequence_sum(a, a, acnt);
    ll bcnt = N / b;
    ll bsum = arithmetic_sequence_sum(b, b, bcnt);
    ll lcnt = N / l;
    ll lsum = arithmetic_sequence_sum(l, l, lcnt);
    ll ans = total - (asum + bsum - lsum);
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
