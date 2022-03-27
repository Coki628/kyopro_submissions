/*
・きっちり自力AC！
・数え上げ
・全体GCDで2以上みたいな話だけど、うまくいくケースはかなり限定されそう。
　で2しか無理っぽいとなり、奇数位置に偶数を置く(しかないと信じる)。
　その中は自由に置けるので、全体で(N/2)!^2
　奇数個はそもそも無理(と信じる)。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

ModTools<mint> mt(1007);

void solve() {
    ll N;
    cin >> N;

    if (N%2 == 1) {
        print(0);
    } else {
        mint ans = mt.fact(N/2).pow(2);
        print(ans);
    }
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
