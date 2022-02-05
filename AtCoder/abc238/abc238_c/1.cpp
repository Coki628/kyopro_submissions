/*
・自力AC！
・等差数列の和
・桁長毎に等差数列の和。最後はうまく削る。これCかぁ…
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll N;
    cin >> N;

    ll prv = 1, d = 1;
    mint ans = 0;
    while (1) {
        ll cur = pow(10, d);
        ll cnt = min(cur, N+1)-prv;
        ans += arithmetic_sequence_sum<mint>(1, 1, cnt);
        if (N+1 <= cur) break;
        prv = cur;
        d++;
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
