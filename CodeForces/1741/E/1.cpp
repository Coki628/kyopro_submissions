/*
・きっちり自力AC！
・到達可否でDP。長さを表す部分が前に来るか後ろに来るかで配る遷移と貰う遷移する。
　なんとなくこどふぉなら復元要求されそうな問題だけど判定だけなので楽。(これはすんなりできた)
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
    auto A = LIST(N);

    vector<ll> dp(N+1);
    dp[0] = 1;
    rep(i, N) {
        if (i+A[i]+1 <= N) {
            dp[i+A[i]+1] |= dp[i];
        }
        if (i-A[i] >= 0) {
            dp[i+1] |= dp[i-A[i]];
        }
    }
    if (dp[N]) YES();
    else NO();
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
