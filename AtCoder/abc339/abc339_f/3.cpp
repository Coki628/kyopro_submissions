/*
ライブラリ整備：任意ModInt
・ちょうどいい機会なので、通常ModIntと仕様を合わせた。
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

#include "combinatorics/ArbitraryModInt.hpp"
#include "numbers/FastPrimeFactorization.hpp"
#include "common/randrange.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<string> A(N);
    cin >> A;

    int p = 1;
    while (not FastPrimeFactorization::is_prime(p)) {
        p = randrange(2, MOD);
    }
    ArbitraryModInt<1>::set_mod(p);
    p = 1;
    while (not FastPrimeFactorization::is_prime(p)) {
        p = randrange(2, MOD);
    }
    ArbitraryModInt<2>::set_mod(p);

    using mint1 = ArbitraryModInt<1>;
    using mint2 = ArbitraryModInt<2>;
    vector<mint1> A1(N);
    vector<mint2> A2(N);
    map<pii, int> C;
    rep(i, N) {
        A1[i] = A[i];
        A2[i] = A[i];
        C[{(int)A1[i], (int)A2[i]}]++;
    }
    ll ans = 0;
    rep(i, N) {
        rep(j, N) {
            auto res1 = A1[i] * A1[j];
            auto res2 = A2[i] * A2[j];
            if (C.count({(int)res1, (int)res2})) {
                ans += C[{(int)res1, (int)res2}];
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
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
