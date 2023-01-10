/*
参考：https://twitter.com/w0mbatt/status/1556058398201745408
・このDP方針だったらもっとすんなり解けてたな。。
　いわゆる、左端開始前・区間内・右端終了後の3状態持つDPみたいなやつ。
　このタイプいつも見落とすんだよな…。意識していきたい。
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
    ll N, L, R;
    cin >> N >> L >> R;
    auto A = LIST(N);

    auto dp = listnd(3, N+1, INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, 3) {
            rep(k, j, 3) {
                if (k == 0) {
                    chmin(dp[k][i+1], dp[j][i]+L);
                } elif (k == 1) {
                    chmin(dp[k][i+1], dp[j][i]+A[i]);
                } else {
                    chmin(dp[k][i+1], dp[j][i]+R);
                }
            }
        }
    }
    ll ans = INF;
    rep(j, 3) {
        chmin(ans, dp[j][N]);
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
