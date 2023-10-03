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
    vector<ll> A(N);
    cin >> A;

    vector<ll> dp(N, INF), prv(N, -1);
    dp[0] = 0;
    rep(i, N - 1) {
        if (chmin(dp[i + 1], dp[i] + abs(A[i + 1] - A[i]))) {
            prv[i + 1] = i;
        }
        if (i + 2 < N) {
            if (chmin(dp[i + 2], dp[i] + abs(A[i + 2] - A[i]))) {
                prv[i + 2] = i;
            }
        }
    }
    
    ll cur = N - 1;
    vector<ll> ans;
    while (cur > 0) {
        ans.eb(cur);
        cur = prv[cur];
    }
    ans.eb(cur);
    reverse(ALL(ans));
    ans++;
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
