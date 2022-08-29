/*
・期待値DPのこと
・自己ループあり、まとめて遷移
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N-1);

    BIT<mint> dp(N);
    rep(i, N-2, -1, -1) {
        // この位置での操作回数1
        mint exp = 0, cost = 1;
        // (この先でかかる分+今回かかる分) * そうなる確率 (を区間でまとめてる)
        exp += (dp.query(i+1, i+A[i]+1)+cost*A[i]) / (A[i]+1);
        // 自己ループ分のコスト * そうなる確率
        exp += cost * 1/(A[i]+1);
        // 自己ループ補正(全手数/自己ループじゃない手数)
        exp *= mint(A[i]+1) / A[i];
        dp.add(i, exp);
    }
    mint ans = dp[0];
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
