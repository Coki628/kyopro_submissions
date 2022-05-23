/*
・これは2乗DPなのでTLE想定。。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> T(N), Y(N);
    rep(i, N) {
        cin >> T[i] >> Y[i];
    }

    auto dp = list2d(N+1, K+1, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, K+1) {
            if (T[i] == 1) {
                chmax(dp[i+1][j], Y[i]);
            } else {
                chmax(dp[i+1][j], dp[i][j]+Y[i]);
            }
            if (j+1 <= K) {
                chmax(dp[i+1][j+1], dp[i][j]);
            }
        }
    }
    ll ans = max(dp[N]);
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
