/*
・幾何、角度の取得、射影
・結構だるい。場合分け、本見ながらやった。
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

#include "geometry/Point.hpp"
#include "geometry/Segment.hpp"
#include "geometry/get_degree.hpp"
#include "geometry/project.hpp"

void solve() {
    Point<ld> a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

    // 角度から3点の位置関係を判断
    auto abc = get_degree(a, b, c);
    auto acb = get_degree(a, c, b);
    // bの外側
    if (90 < abc-EPS and abc+EPS < 270) {
        auto res = a.abs(b);
        print(res);
        return;
    }
    // cの外側
    if (90 < acb-EPS and acb+EPS < 270) {
        auto res = a.abs(c);
        print(res);
        return;
    }
    // 射影(垂線を引いた点)
    auto p = project({b, c}, a);
    auto res = a.abs(p);
    print(res);
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
