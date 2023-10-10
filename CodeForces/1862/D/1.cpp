/*
・自力AC！
・組み合わせ、二分探索
・とりあえず種類を増やせばペアを増やせるので、
　目指すN個を超過しない範囲で種類を増やす。これはにぶたんできる。
　残りの半端な数は、重複する種類を1個ずつ増やしていくとすると、
　1個増やす毎に同種類ペアが1個増えるので、これで調整する。
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

    ll kind = bisearch_max(0, INF, [&](ll x) {
        if (mul_overflow(x, x - 1)) {
            return false;
        }
        return x * (x - 1) / 2 <= N;
    });
    ll rest = N - kind * (kind - 1) / 2;
    ll ans = kind + rest;
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
