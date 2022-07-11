/*
・なんとか自力AC！
・2円の交差判定
・円の内包判定が昔やったやつ見つからなくて結局ググった。いつもの高校数学さん。
　これもC++の幾何ライブラリの整備が甘くて、最初Pythonでやったら(なぜかpypyでも)TLE…。
　結局半泣きでC++版を加筆修正して何とかAC。ldで祈るように投げたけど誤差は大丈夫だった。
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
#include "geometry/Circle.hpp"

// 参考：https://manabitimes.jp/math/745
// 円c1と円c2の交差判定
bool intersectCC(Circle<ld> c1, Circle<ld> c2) {
    ld d = hypot(c1.c.x-c2.c.x, c1.c.y-c2.c.y);
    // 2円が離れてる
    if (d > c1.r+c2.r) {
        return false;
    }
    // 一方が他方を内包
    if (d < abs(c1.r-c2.r)) {
        return false;
    }
    return true;
}

void solve() {
    ll N;
    cin >> N;
    ll sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;

    vector<Circle<ld>> C(N);
    rep(i, N) {
        ll x, y, r;
        cin >> x >> y >> r;
        C[i] = {Point<ld>{x, y}, r};
    }
    UnionFind uf(N+2);
    rep(i, N) {
        rep(j, i+1, N) {
            if (intersectCC(C[i], C[j])) {
                uf.merge(i, j);
            }
        }
    }
    rep(i, N) {
        if (intersectCC(C[i], Circle<ld>{Point<ld>{sx, sy}, 0})) {
            uf.merge(i, N);
        }
        if (intersectCC(C[i], Circle<ld>{Point<ld>{tx, ty}, 0})) {
            uf.merge(i, N+1);
        }
    }
    if (uf.same(N, N+1)) {
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
