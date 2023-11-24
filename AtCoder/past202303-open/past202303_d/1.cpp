/*
・きっちり自力AC。
・一見毎回2通りの方法があるように見えるが、
　操作1はひたすら繰り返すとどうなるかが計算で分かるので、
　操作2をやり進めながら、その時点から操作1を繰り返すとどうなるか毎回チェックすればOK。
　「floor(h, 2)減らします」が「floor(h, 2)に減らします」に見えて1WA。。
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
    ll H, a, b, c, d;
    cin >> H >> a >> b >> c >> d;

    ll ans = INF;
    ll h = H, cost = 0;
    while (h > 0) {
        ll rest = ceil(h, a) * b;
        chmin(ans, cost + rest);
        cost += d;
        h -= c;
        h = ceil(h, 2LL);
    }
    chmin(ans, cost);
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
