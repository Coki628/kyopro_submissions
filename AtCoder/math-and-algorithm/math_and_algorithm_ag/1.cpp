/*
・幾何、円の位置関係を判定
・中心からの距離で場合分け。すげーびびりながら投げたけど一発ACできてよかった。。
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

#include "geometry/Circle.hpp"

void solve() {
    Circle<ld> c1, c2;
    cin >> c1.c.x >> c1.c.y >> c1.r;
    cin >> c2.c.x >> c2.c.y >> c2.r;

    ld d = c1.c.abs(c2.c);
    if (max(c1.r, c2.r)-min(c1.r, c2.r) > d+EPS) {
        print(1);
    } elif (abs(max(c1.r, c2.r)-min(c1.r, c2.r)-d) < EPS) {
        print(2);
    } elif (abs(c1.r+c2.r-d) < EPS) {
        print(4);
    } elif (c1.r+c2.r < d-EPS) {
        print(5);
    } else {
        print(3);
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
