/*
・気合で間に合うか試してみてTLE。。
　以前にも同じこと試しててうけたね。まるで成長していない。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, P;
    cin >> N >> P;
    string S;
    cin >> S;

    ll dp[2][10000][2] = {};
    dp[0][0][0] = 1;
    ll ans = 0;
    rep(i, N) {
        ll a = S[i] - '0';
        rep(j, P) {
            dp[(i + 1) % 2][j][0] += dp[i % 2][j][0];
            dp[(i + 1) % 2][(j * 10 + a) % P][1] += dp[i % 2][j][0];
            dp[(i + 1) % 2][(j * 10 + a) % P][1] += dp[i % 2][j][1];
            dp[i % 2][j][0] = 0;
            dp[i % 2][j][1] = 0;
        }
        ans += dp[(i + 1) % 2][0][1];
    }
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
