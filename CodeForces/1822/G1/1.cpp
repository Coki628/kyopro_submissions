/*
・これは自力TLE。。
　平方数全列挙して全部見ればいけると思ったらダメだった。。
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
    ll M = max(A);
    ll x = 2;
    while (x * x <= M) {
        ll xx = x * x;
        map<ll, ll> C2, C3;
        rep(i, N) {
            if (A[i] % x == 0) {
                C2[A[i] / x]++;
            }
            if (A[i] % xx == 0) {
                C3[A[i] / xx]++;
            }
        }
        for (auto [k, v] : C3) {
            ans += v * C2[k] * C[k];
        }
        x++;
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
