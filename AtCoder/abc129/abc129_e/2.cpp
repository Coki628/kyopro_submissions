/*
・2変数の桁DP
・最初、a+b = 2 の遷移で繰り上がりしたいけどsmallerフラグ持つと、
　下からできないから無理じゃん、って悩んだけど、
　a+b == a^b の条件を考えると a+b = 2 の遷移は無理なんだと分かった。
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

    auto dp = listnd(N + 1, 2, (mint)0);
    dp[0][0] = 1;
    rep(i, N) {
        ll x = S[i] - '0';
        rep(j, 2) {
            if (dp[i][j] == 0) continue;
            rep(a, 2) {
                rep(b, 2) {
                    if (a and b) continue;
                    ll ab = a + b;
                    if (j == 0 && ab > x) continue;
                    ll nxj = j | (ab < x);
                    dp[i + 1][nxj] += dp[i][j];
                }
            }
        }
    }
    mint ans = sum(dp[N]);
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
