/*
・きっちり自力AC！
・DPする。最近DP初級みたいのは本当にCによく出るね。
　でもこれはdiffが緑diff手前くらいになったらしくて、少し安心した。
　そんなに万人がDPできる時代はさすがにまだ来ないだろう…多分。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll N, M, K;
    cin >> N >> M >> K;

    auto dp = list2d(N+1, K+1, (mint)0);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, K+1) {
            rep(k, 1, M+1) {
                if (j+k <= K) {
                    dp[i+1][j+k] += dp[i][j];
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
