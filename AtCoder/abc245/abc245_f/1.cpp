/*
・きっちり自力AC！
・有向グラフの閉路検出、メモ化再帰
・最初SCCでやろうと思ったけど、サイクルに含まれる頂点じゃなくて、
　サイクルに到達できる頂点だったから、なら再帰で見に行こうという方針に。
・閉路検出しながら、そういう頂点に到達したかどうかを記録するメモ化再帰をやる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
    }

    vector<ll> has_cycle(N), visited(N, -1);
    auto dfs = [&](auto&& f, ll u) -> bool {
        if (visited[u] == 0) {
            has_cycle[u] = 1;
            return 1;
        } elif (visited[u] == 1) {
            return has_cycle[u];
        }
        visited[u] = 0;
        ll res = 0;
        for (auto v : nodes[u]) {
            res |= f(f, v);
        }
        has_cycle[u] = res;
        visited[u] = 1;
        return res;
    };
    rep(i, N) {
        if (visited[i] == -1) {
            dfs(dfs, i);
        }
    }
    ll ans = sum(has_cycle);
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
