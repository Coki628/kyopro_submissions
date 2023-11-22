/*
・きっちり自力AC！
・K番目の値、にぶたん、桁DP
・にぶたん内を桁DPで数え上げて、K以上の最小値から答えを探す。
　4を使わないには、一番標準の桁DPに4の遷移に関する条件1個足すだけ。
　絶対もっと賢い解法あってこれは非想定って思ったけど、
　結構手際良く書けたので問題なし。
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
    ll K;
    cin >> K;

    ll ans = bisearch_min(0, INF, [&](ll x) {
        string S = tostr(x);
        ll N = S.size();
        auto dp = listnd(N + 1, 2, 0LL);
        dp[0][0] = 1;
        rep(i, N) {
            ll num = S[i] - '0';
            rep(j, 2) {
                rep(d, 10) {
                    if (d == 4) continue;
                    if (j == 0 and d > num) continue;
                    ll nxj = j | (d < num);
                    dp[i + 1][nxj] += dp[i][j];
                }
            }
        }
        ll res = dp[N][0] + dp[N][1];
        // 0を除く
        res--;
        return res >= K;
    });
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
