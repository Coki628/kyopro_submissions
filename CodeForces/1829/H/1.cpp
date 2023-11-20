/*
・きっちり自力AC！
・AND、部分和DP
・ANDの部分和DPみたいにやる。これGより全然簡単じゃあ…。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    ll M = 64;
    mint dp[N + 1][M] = {};
    dp[0][M - 1] = 1;
    rep(i, N) {
        rep(j, M) {
            dp[i + 1][j] += dp[i][j];
            dp[i + 1][j & A[i]] += dp[i][j];
        }
    }
    dp[N][M - 1]--;
    mint ans = 0;
    rep(j, M) {
        if (popcount(j) == K) {
            ans += dp[N][j];
        }
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
