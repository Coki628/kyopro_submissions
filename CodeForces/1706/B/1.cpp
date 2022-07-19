/*
・きっちり自力AC！
・色毎にindex分けてDP。
　直前に取った要素のindex偶奇を状態に持って、直前と偶奇が違えば取れるみたいにやる。
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
    rep(i, N) A[i]--;

    vvl adj(N);
    rep(i, N) {
        adj[A[i]].eb(i);
    }
    vector<ll> ans(N);
    rep(i, N) {
        ll n = adj[i].size();
        auto dp = list2d(n+1, 2, -INF);
        dp[0][0] = dp[0][1] = 0;
        rep(j, n) {
            rep(k, 2) {
                chmax(dp[j+1][k], dp[j][k]);
                if (k%2 != adj[i][j]%2) {
                    chmax(dp[j+1][1-k], dp[j][k]+1);
                }
            }
        }
        ans[i] = max(dp[n][0], dp[n][1]);
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
