/*
・きっちり自力AC！
・整理すると各頂点で「到達可な頂点数-出次数-1」。2乗効くので各頂点を根にDFS。
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
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
    }

    ll ans = 0;
    rep(r, N) {
        vector<int> visited(N);
        auto dfs = [&](auto &&f, ll u) {
            if (visited[u]) return;
            visited[u] = 1;
            for (auto v : nodes[u]) {
                f(f, v);
            }
        };
        dfs(dfs, r);
        ll res = sum(visited) - (int)nodes[r].size() - 1;
        ans += res;
    }
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
