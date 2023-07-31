/*
・きっちり自力AC！
・括弧列を+-に見る典型でDP
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
    string S;
    cin >> S;
    ll N = S.size();

    auto dp = listnd(N + 1, N + 1, (mint)0);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, N + 1) {
            if (dp[i][j] == 0) continue;
            if (S[i] == '?' or S[i] == '(') {
                dp[i + 1][j + 1] += dp[i][j];
            }
            if ((S[i] == '?' or S[i] == ')') and j > 0) {
                dp[i + 1][j - 1] += dp[i][j];
            }
        }
    }
    mint ans = dp[N][0];
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
