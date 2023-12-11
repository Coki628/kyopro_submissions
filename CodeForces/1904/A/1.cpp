/*
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
    ll a, b, xk, yk, xq, yq;
    cin >> a >> b >> xk >> yk >> xq >> yq;

    map<pll, ll> C;
    C[{xk + a, yk + b}]++;
    C[{xk - a, yk + b}]++;
    C[{xk + a, yk - b}]++;
    C[{xk - a, yk - b}]++;
    C[{xq + a, yq + b}]++;
    C[{xq - a, yq + b}]++;
    C[{xq + a, yq - b}]++;
    C[{xq - a, yq - b}]++;
    if (a != b) {
        C[{xk + b, yk + a}]++;
        C[{xk - b, yk + a}]++;
        C[{xk + b, yk - a}]++;
        C[{xk - b, yk - a}]++;
        C[{xq + b, yq + a}]++;
        C[{xq - b, yq + a}]++;
        C[{xq + b, yq - a}]++;
        C[{xq - b, yq - a}]++;
    }
    ll ans = 0;
    for (auto [k, v] : C) {
        if (v == 2) ans++;
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
