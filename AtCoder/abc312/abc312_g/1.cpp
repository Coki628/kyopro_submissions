/*
参考：https://twitter.com/kyopro_friends/status/1685287444047142912
・自力ならず。これは解きたかったな…。
・余事象、木DP
・3つ組でパスになるのを数えて全体から引いた。
　自身を真ん中として両端になりうるのを探すと、
　親側と子側でのペアと子側同士のペアを数えればよくて、
　これは両方木DPで数えられる。
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

ll nC3(ll n) {
    return (n * (n - 1) * (n - 2)) / 6;
}

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    ll ans = nC3(N);
    vector<ll> sz(N);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        sz[u]++;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            // (子側, 自分, 子側)
            ans -= (sz[u] - 1) * sz[v];
            sz[u] += sz[v];
        }
        ll parcnt = N - sz[u];
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            // (親側, 自分, 子側)
            ans -= parcnt * sz[v];
        }
    };
    dfs(dfs, 0, -1);
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
