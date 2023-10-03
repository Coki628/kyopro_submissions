/*
・DP復元
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
    vector<ll> A(N + 1), B(N + 1);
    rep(i, 2, N + 1) {
        cin >> A[i];
    }
    rep(i, 3, N + 1) {
        cin >> B[i];
    }

    vector<ll> dp(N + 1, INF), prv(N + 1, -1);
    dp[1] = 0;
    rep(i, 2, N + 1) {
        if (chmin(dp[i], dp[i - 1] + A[i])) {
            prv[i] = i - 1;
        }
        if (chmin(dp[i], dp[i - 2] + B[i])) {
            prv[i] = i - 2;
        }
    }

    ll cur = N;
    vector<ll> ans;
    while (cur > 1) {
        ans.eb(cur);
        cur = prv[cur];
    }
    ans.eb(cur);
    reverse(ALL(ans));
    print(ans.size());
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
