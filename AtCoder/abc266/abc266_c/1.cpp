/*
・自力AC！
・幾何
・角度4箇所求める。自分のライブラリがラジアン返すように直してたの忘れててタイムロス…。
　次ミスらないようにライブラリの引数にdegreeにするかどうか入れた。
・なんかTL見てたらだいたいの人は外積の正負で解いてた。
　外積の正負で回転方向が分かるってやつ。
　なんかねー、外積は数学であんま染みついてないからこういう時活かせないんだよね…。
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

#include "geometry/Point.hpp"
#include "geometry/angle.hpp"
#include "geometry/degrees.hpp"

void solve() {
    vector<Point<ld>> P;
    rep(i, 4) {
        ld x, y;
        cin >> x >> y;
        P.eb(x, y);
    }

    rep(i, 4) {
        auto p1 = P[i];
        auto p2 = P[(i+1)%4];
        auto p3 = P[(i+2)%4];
        auto res = angle(p3, p2, p1);
        if (res+EPS >= 180) {
            No();
            return;
        }
    }
    Yes();
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
