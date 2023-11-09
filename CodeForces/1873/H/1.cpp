/*
・自力AC！
・グラフ上のゲーム、なもりグラフの閉路検出
・ゲーム内容をまとめると、逃げる方がなもり閉路に入る前(あるいは同着)に
　追う方がそこに着いてしまうようなら逃げられず負ける。
　本番中はなもりグラフの閉路検出は別の問題から引っ張ってきたけど、
　なんか通算4回くらい同じようなDFS書いてたので、ライブラリ化した。
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

#include "graph/cycle_detection_for_namori.hpp"
#include "graph/bfs.hpp"

void solve() {
    ll N, a, b;
    cin >> N >> a >> b;
    a--, b--;
    vvi nodes(N);
    rep(i, N) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    // サイクルの位置を特定
    auto cycle = cycle_detection_for_namori(nodes);

    // 頂点bから一番近いなもり閉路の頂点
    ll x = -1;
    auto dfs = [&](auto&& f, ll u, ll prv) -> bool {
        if (cycle[u]) {
            x = u;
            return true;
        }
        ll res = INF;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            if (f(f, v, u)) {
                return true;
            }
        }
        return false;
    };
    dfs(dfs, b, -1);

    auto dist = bfs(nodes, {(int)x});
    if (dist[a] > dist[b]) {
        YES();
    } else {
        NO();
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
