/*
・なんとか自力AC！
・幾何、三角関数、回転行列、二分探索
・幾何でうっ、ってなりつつも頑張って良かった。
　1点は隅に付けるとして浮かせる角度を決め打つと1辺の長さと2点目が一意になり、
　3点目も2点目の座標位置を回転させると求まる。
　この3点目が四角形の内側ならOK、みたいなにぶたんで角度(辺の長さ)を最大化。
　A,B入れ替えて同じことやる。
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

#include "common/bisearch_real.hpp"
#include "geometry/Point.hpp"
#include "geometry/rotate.hpp"
#include "geometry/radians.hpp"

void solve() {
    ld A, B;
    cin >> A >> B;

    auto calc = [&](ld deg) -> bool {
        ld len = B / cos(radians(deg));
        ld h = len * sin(radians(deg));
        Point<ld> p1 = {0, 0}, p2 = {B, h};
        auto p3 = rotate(p1, p2, 60);
        if (p3.x < 0 or p3.y > A) {
            return false;
        } else {
            return true;
        }
    };

    ld ans = 0;
    ld res = bisearch_max(0, 90, calc, 100);
    if (calc(res)) {
        chmax(ans, B / cos(radians(res)));
    }
    swap(A, B);
    res = bisearch_max(0, 90, calc, 100);
    if (calc(res)) {
        chmax(ans, B / cos(radians(res)));
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
