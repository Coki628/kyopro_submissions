/*
・きっちり自力AC！
・制約が小さめ。毎回辺操作してBFSでOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/graph/bfs.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;

    vvi nodes(N);
    rep(i, Q) {
        int op, u, v;
        cin >> op >> u >> v;
        u--; v--;
        if (op == 1) {
            if (find(ALL(nodes[u]), v) == nodes[u].end()) {
                nodes[u].eb(v);
                nodes[v].eb(u);
            } else {
                nodes[u].erase(find(ALL(nodes[u]), v));
                nodes[v].erase(find(ALL(nodes[v]), u));
            }
        } else {
            auto res = bfs(nodes, {u});
            if (res[v] < INF) {
                Yes();
            } else {
                No();
            }
        }
    }
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
