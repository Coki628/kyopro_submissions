/*
・きっちり自力AC！
・A,Bの偶奇は異なる。2種類の操作のどちらを行っても偶奇は同じなので、偶奇だけ見る。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll N, X, Y;
    cin >> N >> X >> Y;
    auto A = LIST(N);

    ll oe = 0;
    rep(i, N) {
        oe ^= A[i]&1;
    }
    if (((X&1) == (Y&1)) ^ oe) {
        print("Alice");
    } else {
        print("Bob");
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
