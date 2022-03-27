/*
・きっちり自力AC！
・DPしてやるのが確実。
　でもこれで灰diffスレスレの茶diffなのとかはまじで末世のインフレ感…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vvl A(2);
    A[0] = LIST(N);
    A[1] = LIST(N);

    auto dp = list2d(N+1, 2, false);
    dp[1][0] = dp[1][1] = true;
    rep(i, 1, N) {
        rep(j, 2) {
            if (not dp[i][j]) continue;
            rep(k, 2) {
                if (abs(A[j][i-1]-A[k][i]) <= K) {
                    dp[i+1][k] = true;
                }
            }
        }
    }
    if (dp[N][0] or dp[N][1]) {
        Yes();
    } else {
        No();
    }
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
