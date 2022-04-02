/*
・なんとか自力AC…。
・三角関数
・危ない。。たまにこういう数学出ると焦るから…。
　座標からatan2で角度求めて、斜辺の長さ1が分かってるので後はsin,cosで。
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
    ll x, y;
    cin >> x >> y;

    if (x == 0) {
        print(mkp(0, 1));
        return;
    } elif (y == 0) {
        print(mkp(1, 0));
        return;
    }

    pair<ld, ld> ans = {cos(atan2(y, x)), sin(atan2(y, x))};
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
