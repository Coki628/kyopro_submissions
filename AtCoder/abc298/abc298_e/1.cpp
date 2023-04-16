/*
・きっちり自力AC！
・確率DP
・Nは小さい。DPで全結果の状態についてそうなる確率を求めておいて、先手勝ちの分を全部足す。
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
    ll N, A, B, P, Q;
    cin >> N >> A >> B >> P >> Q;

    auto dp = listnd(2, N + 1, N + 1, mint(0));
    dp[0][A][B] = 1;
    rep(i, N) {
        rep(j, N) {
            rep(turn, 2) {
                if (dp[turn][i][j] == 0) continue;
                if (turn == 0) {
                    rep(ii, 1, P + 1) {
                        dp[1 - turn][min(i + ii, N)][j] += dp[turn][i][j] / P;
                    }
                } else {
                    rep(jj, 1, Q + 1) {
                        dp[1 - turn][i][min(j + jj, N)] += dp[turn][i][j] / Q;
                    }
                }
            }
        }
    }
    mint ans = 0;
    rep(j, N) {
        ans += dp[1][N][j];
    }
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
