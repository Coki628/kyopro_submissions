/*
・これはTLE。。
・区間状態DP
・50万*10ビット*3は無理だった…。でもなんかTL見た限りこっちで通した人もいるっぽいんだよね。
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
    string S;
    cin >> S;
    ll N = S.size();

    ll dp[2][3][1 << 10] = {};
    dp[0][0][0] = 1;
    rep(i, N) {
        ll a = toint(S[i]);
        rep(j, 3) {
            rep(k, 1 << 10) {
                dp[(i + 1) % 2][0][k] += dp[i % 2][0][k];
                dp[(i + 1) % 2][2][k] += dp[i % 2][1][k];
                dp[(i + 1) % 2][2][k] += dp[i % 2][2][k];
                dp[(i + 1) % 2][1][k ^ (1 << a)] += dp[i % 2][0][k];
                dp[(i + 1) % 2][1][k ^ (1 << a)] += dp[i % 2][1][k];
                dp[i % 2][0][k] = 0;
                dp[i % 2][1][k] = 0;
                dp[i % 2][2][k] = 0;
            }
        }
    }
    ll ans = dp[N % 2][1][0] + dp[N % 2][2][0];
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
