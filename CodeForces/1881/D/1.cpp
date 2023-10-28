/*
・きっちり自力AC！
・約数、倍数、素因数分解
・題意の操作は素因数単位で移動させてく感じなので、
　全部素因数分解して均等に分けれるかチェックする。
　素因数分解は√かかるやつでもいけるかもしれないけど、
　念のため篩で前計算する方でやった。
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

#include "numbers/Eratosthenes.hpp"

Eratosthenes era(1000000);

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    map<ll, ll> C;
    rep(i, N) {
        for (auto [k, v] : era.factorize(A[i])) {
            C[k] += v;
        }
    }
    for (auto [k, v] : C) {
        if (v % N != 0) {
            NO();
            return;
        }
    }
    YES();
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
