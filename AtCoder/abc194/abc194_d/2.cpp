/*
・自己ループのある期待値DP
・これでもちゃんとACしたけど、確率の逆数使うやつすっかり忘れてた…。
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

    vector<ld> dp(N + 1);
    rep(i, N - 1, 0, -1) {
        // この位置での操作回数1
        ld cost = 1;
        // (この先でかかる分 + 今回かかる分) * そうなる確率
        dp[i] += (dp[i + 1] + cost) * ((N - i) / (ld)N);
        // 自己ループ分のコスト * そうなる確率
        dp[i] += cost * (i / (ld)N);
        // 自己ループ補正(全手数 / 自己ループじゃない手数)
        dp[i] *= N / (ld)(N - i);
    }
    print(dp[1]);
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
