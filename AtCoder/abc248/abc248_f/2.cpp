/*
参考：https://blog.hamayanhamayan.com/entry/2022/04/16/234841
・連結DP
・実は状態は上下の連結/非連結だけを持てばいけるみたい。
　まあ5個も分けなくてもいけるんだろうなとは思ってたけど…。
　で、それを踏まえて遷移書いたけど、何かサンプル2が合わない。
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
// using mint = ModInt<MOD>;
#include "template.hpp"

#include "combinatorics/ArbitraryModInt.hpp"
using mint = ArbitraryModInt;

mint dp[3007][3007][2];

void solve() {
    ll N, P;
    cin >> N >> P;
    mint::set_mod(P);

    // dp[i][m][j] := i列目の頂点まで左右を繋いで、辺をm本削除して、最後の状態がjの通り数
    // j = 0: 上下非連結, 1: 上下連結
    dp[0][1][1] = 2; // L
    dp[0][0][1] = 1; // 匚
    dp[0][1][0] = 1; // ニ
    rep(i, N-2) {
        rep(m, N) {
            // L
            dp[i+1][m+1][0] += (dp[i][m][0]+dp[i][m][1]) * 2;
            // 匚
            dp[i+1][m][1] += (dp[i][m][0]+dp[i][m][1]);
            // ニ
            dp[i+1][m+1][0] += dp[i][m][0];
            dp[i+1][m+1][1] += dp[i][m][1];
            // 一
            dp[i+1][m+2][0] += dp[i][m][1] * 2;
        }
    }
    vector<mint> ans(N);
    rep(m, 1, N) {
        // 右端の縦線の有無を決める
        ans[m] = dp[N-2][m-1][1] + dp[N-2][m][0] + dp[N-2][m][1];
    }
    ans.erase(ans.begin());
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
