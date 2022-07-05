/*
・古の高難度気まぐれ埋め
・きっちり自力AC！いいね。
・グラフ、木に帰着、木DP
・まず頂点0は自己ループさせる。これでKちょうどではなくK以下とできる。
　逆にこれをやらないと、全頂点からKぴったりとか無理。(辺N本しかないし)
　で、元々連結だと書いてあるので、ここからは木DPする。
　部分木の一番長い所がKに達した所で切る、みたいのをやればOK。
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

#include "graph/bfs.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);
    rep(i, N) A[i]--;

    ll ans = 0;
    if (A[0] != 0) {
        ans++;
    }
    vvi nodes(N);
    rep(i, 1, N) {
        nodes[A[i]].eb(i);
    }
    auto dist = bfs(nodes, {0});
    vector<ll> dp(N);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            // ここで切ってリセット
            if (dp[v] == K) {
                ans++;
            } else {
                chmax(dp[u], dp[v]);
            }
        }
        // 自身がKより遠いか、Kより遠い頂点を1つでも部分木に残していたら+1
        if (dist[u] > K or dp[u] > 0) {
            dp[u]++;
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
