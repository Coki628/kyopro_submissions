/*
ライブラリ整備：二重頂点連結成分分解、Block Cut Tree
・BCT構築して、関節点の周辺がどうなるか木DPで部分木見て解く。
　2回通る → 関節点 と紐付けることや、パスではなく関節点を軸にして、
　その頂点を通るパスの通り数を数える主客転倒っぽい感じなど、
　(自分的には)考察要素があって普通に頑張って解いた。
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
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "graph/BlockCutTree.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
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
    ll ans = 0;
    vector<ll> sz(K);
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        sz[u] = bct.size(u);
        for (auto v : bct[u]) {
            if (v == prv) continue;
            f(f, v, u);
            sz[u] += sz[v];
        }
        if (bct.is_articulation(u)) {
            ll sm = N - sz[u];
            for (auto v : bct[u]) {
                if (v == prv) continue;
                ans += sm * sz[v];
                sm += sz[v];
            }
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
