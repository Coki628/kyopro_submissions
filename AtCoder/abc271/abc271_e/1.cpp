/*
・きっちり自力AC！
・in-place DP
・(連続しない)部分列なのでDP方針で考えると、　
　K個中i番目の辺まで見て今頂点j、のDPで前の状態上書きなので、
　じゃあi側の添字つぶせるね、となる。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vector<array<ll, 3>> edges;
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        edges.pb({u, v, c});
    }
    auto E = LIST(K);
    rep(i, K) E[i]--;

    vector<ll> dp(N, INF);
    dp[0] = 0;
    rep(i, K) {
        auto [u, v, c] = edges[E[i]];
        chmin(dp[v], dp[u]+c);
    }
    ll ans = dp[N-1] < INF ? dp[N-1] : -1;
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
