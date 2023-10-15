/*
・普通に通したけど、念入りにオーバーフロー判定入れる必要がある。
　実際はこんなことやっぱりしなくて良くて、　
　素因数2,3だけであるべきなんだから、
　2,3で割れるだけ割って1かどうか見ればいいだけだった。
　まじで頭ついてない…。
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

    ll x = 1;
    while (1) {
        ll y = 1;
        while (1) {
            if (not mul_overflow(x, y) and x * y == N) {
                Yes();
                return;
            }
            if (mul_overflow(y, 3LL)) {
                break;
            }
            y *= 3;
        }
        if (mul_overflow(x, 2LL)) {
            break;
        }
        x *= 2;
    }
    No();
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
