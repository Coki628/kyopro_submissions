/*
・dojo set_d_5_2
・きっちり自力AC！
・素因数2,5があると末尾に0が増えるはず。すると奇数だと2がないので無理で、
　偶数なら2はたくさんあるので素因数5がいくつ含まれるか考える。
　色々考えると、素因数5が増えるところ→5冪以上になったところを検討すればよくて、
　偶数しかない都合上5冪*2のところで1つ増えると予想できる。
・昔解いた時よりはいくらかマシに数学考察ができたと思われる。
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
    ll N;
    cin >> N;

    if (N%2 == 1) {
        print(0);
        return;
    }

    ll ans = 0, d = 1;
    while (1) {
        ll a = pow(5, d) * 2;
        if (a > N) break;
        ans += N / a;
        d++;
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
