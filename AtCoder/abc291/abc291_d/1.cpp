/*
・きっちり自力AC！
・最初任意箇所で数字ダブりなしの通り数かと思っちゃって悩んだ。
　よく見ると隣接だけなので直前の状態持っていつものDP。
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
    auto A = listnd(2, N, 0LL);
    rep(i, N) {
        cin >> A[0][i] >> A[1][i];
    }

    auto dp = listnd(N + 1, 2, (mint)0);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, 2) {
            rep(k, 2) {
                if (i == 0 or A[j][i - 1] != A[k][i]) {
                    dp[i + 1][k] += dp[i][j];
                }
            }
        }
    }
    mint ans = dp[N][0] + dp[N][1];
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
