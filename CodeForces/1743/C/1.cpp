/*
・きっちり自力AC！
・その位置のフタを動かしたかの状態持ってDPした。
　フタを手前に動かす方が頭使って面倒そうに思えたから、
　リバースしてフタを前に動かすかどうか、とした。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;
    auto A = LIST(N);

    reverse(ALL(S));
    reverse(ALL(A));
    auto dp = listnd(2, N+1, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        if (S[i] == '1') {
            chmax(dp[1][i+1], dp[0][i]);
            chmax(dp[1][i+1], dp[1][i] + A[i]);
        }
        chmax(dp[0][i+1], dp[0][i] + (S[i] == '1' ? A[i] : 0));
        chmax(dp[0][i+1], dp[1][i] + A[i]);
    }
    ll ans = max(dp[0][N], dp[1][N]);
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
