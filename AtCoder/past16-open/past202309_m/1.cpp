/*
・きっちり自力AC！
・幾何、線分の交差判定
・これは幾何ライブラリの準備があったので、貼るだけになった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "geometry/intersect.hpp"

void solve() {
    ll a1, b1, c1, d1, a2, b2, c2, d2;
    cin >> a1 >> b1 >> c1 >> d1 >> a2 >> b2 >> c2 >> d2;

    YesNo(intersect(Segment<ld>{{a1, b1}, {c1, d1}}, {{a2, b2}, {c2, d2}}));
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
