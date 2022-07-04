/*
・これは自力WA。
・重複除去の考慮が足りてない。例えばlen=4で4,4,4,4みたいのは消してるけど、
　len=2で出てくる4,4みたいな約数の方で出てくる分を消せてない。
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

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ModTools<mint> mt(N);
    auto C = Counter(A);
    mint ans = 0;
    for (auto [k, v] : C) {
        if (v >= 2) {
            ans += mint(2).pow(v) - v - 1;
            if (k > 1) {
                ans -= mt.nCr(v, k);
            }
        }
    }
    vector<ll> C2(N+1);
    rep(i, N) {
        for (auto div : divisors(A[i])) {
            if (div <= N) {
                C2[div]++;
            }
        }
    }
    rep(len, 2, N+1) {
        ans += mt.nCr(C2[len], len);
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
