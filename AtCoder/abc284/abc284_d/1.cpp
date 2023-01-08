/*
・きっちり自力AC！
・高速素因数分解
・ほんとは3乗根までの素数を探すみたいにやるみたいだけど、
　まあ高速素因数分解貼ったよね…。これで9*10^18でも動作することが分かったね。
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

#include "numbers/FastPrimeFactorization.hpp"

void solve() {
    ll N;
    cin >> N;
    pll ans;
    for (auto [k, v] : FastPrimeFactorization::factorize(N)) {
        if (v == 2) {
            ans.first = k;
        } else if (v == 1) {
            ans.second = k;
        } else {
            assert(0);
        }
    }
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
