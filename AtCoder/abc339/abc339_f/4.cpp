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

#include "combinatorics/DynamicModInt64.hpp"
#include "random/rand_prime.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<string> S(N);
    cin >> S;

    DynamicModInt64<>::set_mod(rand_prime(INF / 10, INF));
    using mint = DynamicModInt64<>;

    vector<mint> A(N);
    rep(i, N) {
        A[i] = S[i];
    }
    auto C = Counter(A);
    ll ans = 0;
    rep(i, N) {
        rep(j, N) {
            auto res = A[i] * A[j];
            if (C.count(res)) {
                ans += C[res];
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
