/*
参考：https://drken1215.hatenablog.com/entry/2019/06/21/230200
・累積和同時進行DP
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), B(M);
    cin >> A >> B;

    auto dp = listnd(N + 1, M + 1, (mint)0);
    auto acc = listnd(N + 1, M + 1, (mint)0);
    rep(i, 1, N + 1) {
        rep(j, 1, M + 1) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] += acc[i - 1][j - 1] + 1;
            }
            // rep(k, i + 1) {
            //     rep(l, j + 1) {
            //         acc[i][j] += dp[k][l];
            //     }
            // }
            acc[i][j] =
                dp[i][j] + acc[i - 1][j] + acc[i][j - 1] - acc[i - 1][j - 1];
        }
    }
    mint ans = 1;
    rep(i, 1, N + 1) {
        rep(j, 1, M + 1) {
            ans += dp[i][j];
        }
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
