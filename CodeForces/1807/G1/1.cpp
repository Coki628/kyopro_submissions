/*
・きっちり自力AC。
・部分和DP
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    sort(ALL(A));
    if (A[0] != 1) {
        NO();
        return;
    }
    ll M = A.back();
    auto dp = listnd(N + 1, M + 1, 0);
    dp[0][0] = 1;
    rep(i, N) {
        rep(j, M + 1) {
            if (dp[i][j]) {
                dp[i + 1][j] = 1;
                if (j + A[i] <= M) {
                    dp[i + 1][j + A[i]] = 1;
                }
            }
        }
    }
    rep(i, N - 1, 0, -1) {
        if (not dp[i][A[i]]) {
            NO();
            return;
        }
    }
    YES();
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
