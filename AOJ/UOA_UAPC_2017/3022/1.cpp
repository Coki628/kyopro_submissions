/*
ライブラリ整備：二重頂点連結成分分解、Block Cut Tree
・BCT構築して、関節点切った時どうなるか木DPで部分木見て解く。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "common/input.hpp"
#include "common/print.hpp"
#include "common/sum.hpp"
#include "common/chmax.hpp"

#include "graph/BlockCutTree.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> W(N);
    cin >> W;
    vvi nodes(N);
    rep(i, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    BlockCutTree bct(nodes);
    ll K = bct.size();
    vector<ll> W2(K);
    rep(u, N) {
        W2[bct.id(u)] += W[u];
    }
    ll wsm = sum(W);
    vector<ll> dp(K), ans(N, wsm);
    rep(u, N) {
        ans[u] -= W[u];
    }
    auto groups = bct.get_groups();
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        dp[u] = W2[u];
        for (auto v : bct[u]) {
            if (v == prv) continue;
            f(f, v, u);
            dp[u] += dp[v];
        }
        if (bct.is_articulation(u)) {
            ll mx = wsm - dp[u];
            for (auto v : bct[u]) {
                if (v == prv) continue;
                chmax(mx, dp[v]);
            }
            assert(groups[u].size() == 1);
            ans[groups[u][0]] = mx;
        }
    };
    dfs(dfs, 0, -1);
    print(ans, "\n");
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
