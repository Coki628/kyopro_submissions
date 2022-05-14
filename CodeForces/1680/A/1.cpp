/*
・きっちり自力AC！
・区間が重なるかどうかで場合分け。この判定たまに出るけど
　いつもこんがらがるからライブラリに助けられてる。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "segment/merge_segment.hpp"

void solve() {
    ll l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;

    ll ans = l1 + l2;
    ll len = merge_segment({l1, r1}, {l2, r2});
    if (len != r1-l1+1 + r2-l2+1) {
        chmin(ans, max(l1, l2));
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
