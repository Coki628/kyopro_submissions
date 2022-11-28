/*
・きっちり自力AC！これはすぐだった。多分本日のハイライト。。
・題意を整理すると、転置してソートして比較、で良さそう。実際それで問題なくAC。
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

#include "grid/transpose.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> S(H), T(H);
    cin >> S >> T;

    S = transpose(S);
    T = transpose(T);
    sort(ALL(S));
    sort(ALL(T));
    if (S == T) {
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
