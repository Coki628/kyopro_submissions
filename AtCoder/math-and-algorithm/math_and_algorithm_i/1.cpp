/*
・部分和DPした。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, S;
    cin >> N >> S;
    auto A = LIST(N);

    ll M = sum(A);
    auto dp = list2d(N+1, M+1, 0LL);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, M+1) {
            if (dp[i][j] == 0) continue;
            dp[i+1][j] += dp[i][j];
            dp[i+1][j+A[i]] += dp[i][j];
        }
    }
    string ans = dp[N][S] ? "Yes" : "No";
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
