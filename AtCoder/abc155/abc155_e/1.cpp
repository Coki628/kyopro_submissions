/*
・dojo set_d_6_2
・なんとか自力AC！
・下から桁DP、繰り上がり
・下の桁から、その桁までの端数の支払い精算が完了しているものとしてDPを進める。
　遷移はその桁で払うか、払わないか。
　場合分け入れちゃったけど、なくても通った…。
・初めて解いた時より、方針がちゃんと頭で整って進められたと思うけど、
　それにしては細部詰め切って通すのに時間かかった(50分くらい？)ので、
　もっと手際よく通していきたいね。。
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
    cin >> S;
    ll N = S.size();

    reverse(ALL(S));
    auto dp = list2d(N+1, 2, INF);
    dp[0][0] = 0;
    rep(i, N) {
        ll a = S[i] - '0';
        rep(j, 2) {
            // この桁で払う
            if (a+j < 10) {
                chmin(dp[i+1][0], dp[i][j]+a+j);
            }
            // 払わない
            if (a+j > 0) {
                chmin(dp[i+1][1], dp[i][j]+10-(a+j));
            }
        }
    }
    ll ans = min(dp[N][0], dp[N][1]+1);
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
