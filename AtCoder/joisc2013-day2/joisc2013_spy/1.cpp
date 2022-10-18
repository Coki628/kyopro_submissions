/*
・これはTLE。N*M=2000*50万=10億はさすがにきつい。
　bitsetでうまいこと速くしようとしたけど、結局Nのi毎に数えたいのでループを回してしまう。
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
    ll N, M;
    cin >> N >> M;
    vvi nodes1(N), nodes2(N);
    ll r1 = -1, r2 = -1;
    rep(i, N) {
        ll p, q;
        cin >> p >> q;
        p-- ; q--;
        if (p == -1) {
            r1 = i;
        } else {
            nodes1[p].eb(i);
        }
        if (q == -1) {
            r2 = i;
        } else {
            nodes2[q].eb(i);
        }
    }
    vector<bitset<2000>> dp1(N), dp2(N);
    auto dfs = [&](auto&& f, ll u, const vvi& nodes, vector<bitset<2000>>& dp) -> void {
        dp[u].set(u);
        for (auto v : nodes[u]) {
            f(f, v, nodes, dp);
            dp[u] |= dp[v];
        }
    };
    dfs(dfs, r1, nodes1, dp1);
    dfs(dfs, r2, nodes2, dp2);

    vector<ll> ans(N);
    rep(i, M) {
        ll r, s;
        cin >> r >> s;
        r--; s--;

        auto res = dp1[r] & dp2[s];
        rep(u, N) {
            if (res[u]) ans[u]++;
        }
    }
    print(ans, '\n');
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
