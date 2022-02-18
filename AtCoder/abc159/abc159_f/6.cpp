/*
参考：https://maspypy.com/atcoder-%e5%8f%82%e5%8a%a0%e6%84%9f%e6%83%b3-2019-03-22abc-159#toc3
・FPS演習
・左右端を網羅するため、片側を固定して、
　累積してくる値をうまく使いまわせるような式変形をする。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"
#include "math/fps/pow_term2.hpp"

void solve() {
    ll N, S;
    cin >> N >> S;
    auto A = LIST(N);

    FPS<mint> fps(S+1);
    mint ans = 0;
    rep(i, N) {
        // F = (F+1)*(1+x*a)
        fps[0]++;
        fps *= SFPS<mint>{{0, 1}, {A[i], 1}};
        ans += fps[S];
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
