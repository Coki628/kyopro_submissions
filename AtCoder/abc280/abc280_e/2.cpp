/*
・期待値DP、貰うDP
・バグらせたのを反省して普通のDPも書き直した。
　配るDPを貰うDPに直したら普通に通った。。
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
    ll N, P;
    cin >> N >> P;

    mint a = (mint)P / 100;
    mint b = (mint)1 - a;
    vector<mint> dp(N+2);
    rep(i, N-1, -1, -1) {
        dp[i] += (dp[i+2] + 1) * a;
        dp[i] += (dp[i+1] + 1) * b;
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
