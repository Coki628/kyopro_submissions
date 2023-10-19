/*
・きっちり自力AC！
・桁DP、総和も数える桁DP
・想定解は天才数え上げだったけど、まあこっちのが汎用性高いしいいでしょう…。
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
    string S;
    cin >> S;
    ll N = S.size();
    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - '0';
    }

    auto dp = listnd(N + 1, 2, 0LL);
    auto sm = listnd(N + 1, 2, 0LL);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, 2) {
            rep(d, 10) {
                if (j == 0 and d > A[i]) continue;
                ll nxj = j | (d < A[i]);
                dp[i + 1][nxj] += dp[i][j];
                sm[i + 1][nxj] += sm[i][j] + dp[i][j] * d;
            }
        }
    }
    ll ans = sm[N][0] + sm[N][1];
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
