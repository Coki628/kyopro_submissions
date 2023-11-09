/*
・これも自力WA。
・最後だけ場合分けかな？と思ったけど変わらず。
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

    auto dp = listnd(N + 1, 2, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, 2) {
            char c = S[i] + j;
            chmax(dp[i + 1][0], dp[i][j]);
            if (i <= N - 2) {
                if (string{c, S[i + 1]} == "AB") {
                    chmax(dp[i + 1][1], dp[i][j] + 1);
                } else if (string{c, S[i + 1]} == "BA") {
                    chmax(dp[i + 1][1], dp[i][j] + 1);
                }
            }
        }
    }
    ll ans = max(dp[N]);
    if (S[0] == 'A') {
        ll i = 0;
        while (S[i] == 'A') {
            i++;
        }
        if (i < N) {
            ans += i - 1;
        }
    }
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
