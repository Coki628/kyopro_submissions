/*
・きっちり自力AC！
・capslockのON/OFFを持ってDP。
　遷移でcapslock押してからshift+aするやつ忘れて1WA。。
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
    ll x, y, z;
    cin >> x >> y >> z;
    string S;
    cin >> S;
    ll N = S.size();

    auto dp = listnd(N + 1, 2, INF);
    dp[0][0] = 0;
    rep(i, N) {
        if (S[i] == 'a') {
            chmin(dp[i + 1][0], dp[i][0] + x);
            chmin(dp[i + 1][1], dp[i][1] + y);
            chmin(dp[i + 1][0], dp[i][1] + z + x);
            chmin(dp[i + 1][1], dp[i][0] + z + y);
        } else if (S[i] == 'A') {
            chmin(dp[i + 1][1], dp[i][1] + x);
            chmin(dp[i + 1][0], dp[i][0] + y);
            chmin(dp[i + 1][1], dp[i][0] + z + x);
            chmin(dp[i + 1][0], dp[i][1] + z + y);
        }
    }
    ll ans = min(dp[N]);
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
