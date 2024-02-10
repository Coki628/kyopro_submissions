/*
・きっちり自力AC！
・にぶたん、等差数列の和、オーバーフロー対策
・公差1の等差数列の和をベースに考えれば、
　例えばN=11なら、1,2,3と来て最後だけ4の代わりに5を置く、
　とすればいいので、等差数列の和がN以下になる最大項数を求めればいい。
　これはにぶたんでできる。なお、値が10^18付近も使ってて大きいので、
　雑にやっても壊れないように128ビット整数を使っておいた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
#include "common/int128.hpp"

void solve() {
    ll N;
    cin >> N;

    ll res = bisearch_max(0, INF, [&](ll x) {
        return arithmetic_sequence_sum<int128>(1, 1, x) <= N;
    });
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
