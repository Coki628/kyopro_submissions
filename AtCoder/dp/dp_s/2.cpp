/*
・dojo set_d_6_1
・きっちり自力AC！
・桁DP
・いわゆるほぼ基本のやつ。
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
    string S;
    ll D;
    cin >> S >> D;
    ll N = S.size();

    auto dp = list3d<mint>(N+1, D, 2, 0);
    dp[0][0][0] = 1;
    rep(i, N) {
        ll a = S[i] - '0';
        rep(j, D) {
            rep(k, 2) {
                if (dp[i][j][k] == 0) continue;
                rep(d, 10) {
                    if (k == 0 and d == a) {
                        dp[i+1][(j+d)%D][0] += dp[i][j][k];
                    } elif (k == 0 and d < a) {
                        dp[i+1][(j+d)%D][1] += dp[i][j][k];
                    } elif (k == 1) {
                        dp[i+1][(j+d)%D][1] += dp[i][j][k];
                    }
                }
            }
        }
    }
    mint ans = sum(dp[N][0]);
    ans--;
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
