/*
・幾何、線分の交差判定
・intersectはpythonから移植してなかったのでやった。
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

#include "geometry/Segment.hpp"
#include "geometry/intersect.hpp"

void solve() {
    Segment<ld> seg1, seg2;
    cin >> seg1.p1.x >> seg1.p1.y;
    cin >> seg1.p2.x >> seg1.p2.y;
    cin >> seg2.p1.x >> seg2.p1.y;
    cin >> seg2.p2.x >> seg2.p2.y;

    if (intersect(seg1, seg2)) {
        Yes();
    } else {
        No();
    }
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
