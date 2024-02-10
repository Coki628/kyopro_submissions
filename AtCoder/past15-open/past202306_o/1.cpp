/*
・きっちり自力AC！
・高速素数判定
・これは、、ボス問に置いていいんだろうか。
　公式解説見たら何やら難しいことを色々やっていたけど、
　高速素因数分解の中に高速な素数判定も入ってるので、
　それでぶん殴ると秒で通る…。
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

#include "numbers/FastPrimeFactorization.hpp"

void solve() {
    ll N, a, b;
    cin >> N >> a >> b;

    ll ans = 0;
    rep(i, N) {
        if (FastPrimeFactorization::is_prime(a * i + b)) {
            ans++;
        }
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
