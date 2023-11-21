/*
・これも自力TLE。。
　終了後、TLの話を見ながら再挑戦。
　平方数からではなく、Aiの約数に注目したけどダメ。
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

#include "numbers/isqrt.hpp"
#include "numbers/FastPrimeFactorization.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    ll ans = 0;
    auto C = Counter(A);
    for (auto [k, v] : C) {
        ans += v * (v - 1) * (v - 2);
    }
    // Aiを固定
    for (auto a : A) {
        for (auto xx : FastPrimeFactorization::divisors(a)) {
            if (xx == 1) continue;
            // 平方数だったらb^2部分として使える
            ll x = isqrt(xx);
            if (x * x == xx) {
                // Aj * Ak
                ans += C[a / x] * C[a / xx];
            }
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
