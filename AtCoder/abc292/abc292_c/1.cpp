/*
・きっちり自力AC！
・約数列挙
・N-abでcdを特定しつつ、両方約数列挙すればペア数も分かる。
　篩の前計算で速くなるけど、多分通るだろうと雑に√Nでやって問題なくAC。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;

    ll ans = 0;
    rep(ab, 1, N) {
        ll cd = N - ab;
        ll c1 = divisors(ab).size();
        ll c2 = divisors(cd).size();
        ans += c1 * c2;
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
