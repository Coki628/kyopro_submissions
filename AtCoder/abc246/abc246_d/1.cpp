/*
・自力ならず…。
・二分探索、3乗根
・(a+b)(a^2+b^2)に式変形したけど、何か良い感じのものが見えて来ず。
　正解は、aを固定してbには単調性があるので、二分探索。
　解はa,bどちらに対してもだいたい3乗くらいにはなるので、
　aを全探索する範囲はNの3乗根くらいまででいい。(cbrtなんて初めて使った。)
　これでaを固定すれば、後はbをN以上になる最小まえ大きくする、
　まあ普通の二分探索。値が大きいし掛け算多いのでオーバーフローは気にしておく。
・結構引っかかってた人多いぽいけど、式変形やりたげな形はブラフだったんだよね…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define CAST_MINT_TO_LL
#include "base.hpp"

// constexpr long long INF = 1e18;
constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;

    ll rn = cbrt(N) + 7;
    ll ans = INF;
    rep(a, rn) {
        ll b = bisearch_min(a-1, rn+7, [&](ll b) {
            if (
                mul_overflow(a, a) or
                mul_overflow(b, b) or
                mul_overflow(a+b, a*a+b*b)
            ) {
                return true;
            }
            return (a+b)*(a*a+b*b) >= N;
        });
        chmin(ans, (a+b) * (a*a+b*b));
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
