/*
・自力AC
・平方数
・x^2+y^2が平方数なら一発、他は2回で行けると信じる。(未証明…)
　詳しく言うと、早々に5000人通してるのを観測して行けると踏む。。
・終了後、冷静に考察すると、1手でx座標動いて2手でy座標動くみたいにすればいいね。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll x, y;
    cin >> x >> y;

    if (x == 0 and y == 0) {
        print(0);
        return;
    }

    ll a = pow(x, 2) + pow(y, 2);
    if (isqrt(a)*isqrt(a) == a) {
        print(1);
    } else {
        print(2);
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
