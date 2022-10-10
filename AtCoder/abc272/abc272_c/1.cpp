/*
・きっちり自力AC！
・偶数にするためには偶+偶か奇+奇が必要なので、
　偶奇で分けてソートして大きい2つ。
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

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    vvl B(2);
    rep(i, N) {
        B[A[i]%2].eb(A[i]);
    }

    ll ans = -1;
    rep(i, 2) {
        sort(B[i].rbegin(), B[i].rend());
        if (B[i].size() >= 2) {
            chmax(ans, B[i][0]+B[i][1]);
        }
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
