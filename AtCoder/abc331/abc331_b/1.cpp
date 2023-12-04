/*
・絶対想定解じゃないだろうと分かりつつ、
　こんな所で場合分けで考察リソース使いたくなくてDPした。
・公式解は3重ループ全探索だった。まあ言われるとそれはそう…。
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
    ll N, S, M, L;
    cin >> N >> S >> M >> L;

    vector<ll> dp(N + 1, INF);
    dp[0] = 0;
    rep(i, N) {
        chmin(dp[min(i + 6, N)], dp[i] + S);
        chmin(dp[min(i + 8, N)], dp[i] + M);
        chmin(dp[min(i + 12, N)], dp[i] + L);
    }
    ll ans = dp[N];
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
