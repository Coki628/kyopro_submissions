/*
・きっちり自力AC！
・縦横独立、部分和DP
・x,yは交互に来る。それぞれ部分和DP(負数はmapでサボった)して両方到達できればOK。
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
    ll N, x, y;
    cin >> N >> x >> y;
    auto A = LIST(N);

    vvl B(2);
    rep(i, N) {
        B[i%2].eb(A[i]);
    }
    vector<ll> dist = {x, y};
    rep(p, 2) {
        ll n = B[p].size();
        vector<HashMap<ll, int>> dp(n+1);
        dp[0][0] = 1;
        rep(i, n) {
            for (auto [k, v] : dp[i]) {
                if (not (p == 0 and i == 0)) dp[i+1][k-B[p][i]] = 1;
                dp[i+1][k+B[p][i]] = 1;
            }
        }
        if (not dp[n].count(dist[p])) {
            No();
            return;
        }
    }
    Yes();
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
