/*
・一般グラフ、単純パス、経路復元
・BFSで前の頂点なり持つ方法もあると思うけど、
　DFSの章だったのでDFSで戻り時に拾ってくるやつにした。
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
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<int> visited(N);
    vector<ll> ans;
    auto dfs = [&](auto&& f, ll u) -> bool {
        if (visited[u]) return false;
        visited[u] = true;
        if (u == N - 1) {
            ans.eb(u);
            return true;
        }
        for (auto v : nodes[u]) {
            if (f(f, v)) {
                ans.eb(u);
                return true;
            }
        }
        return false;
    };
    dfs(dfs, 0);
    reverse(ALL(ans));
    ans++;
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
