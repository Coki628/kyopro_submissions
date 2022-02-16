/*
・dojo set_d_3_4
・自力AC！でもこれは何となくこういうの昔あったよねって思い出せたからかも。
・LIS
・後ろからLISする。そこがボトルネックになるはずなので答え。
・壊れてたLISライブラリ直せたから、それはちょうどよかった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/common/LIS.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    reverse(ALL(A));
    auto res = LIS(A, true);
    ll ans = res.size();
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
