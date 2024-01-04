/*
ライブラリ整備：区間辺グラフ
・区間辺2-SATや区間辺SCCと仕様を合わせた。
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

#include "graph/RangeEdgedGraph.hpp"

void solve() {
    ll N, Q, s;
    cin >> N >> Q >> s;
    s--;

    auto dijkstra = [](const vvpil &nodes, const vector<int> &src, int goal = -1) {
        int N = nodes.size();
        vector<ll> res(N, numeric_limits<ll>::max() / 2);
        priority_queue<pli, vector<pli>, greater<pli>> que;
        for (auto s : src) {
            res[s] = 0;
            que.push({0, s});
        }
        while (que.size()) {
            auto [dist, u] = que.top();
            que.pop();
            if (u == goal) return res;
            if (res[u] < dist) continue;
            for (auto [v, cost] : nodes[u]) {
                if (chmin(res[v], dist + cost)) {
                    que.push({dist + cost, v});
                }
            }
        }
        return res;
    };

    RangeEdgedGraph reg(N);
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            reg.add_edge(u, v, w);
        } elif (op == 2) {
            ll v, l, r, w;
            cin >> v >> l >> r >> w;
            v--; l--;
            reg.add_edges(v, {l, r}, w);
        } else {
            ll v, l, r, w;
            cin >> v >> l >> r >> w;
            v--; l--;
            reg.add_edges({l, r}, v, w);
        }
    }

    // [N,2*N)に元グラフの頂点がある
    auto res = subarray(dijkstra(reg.nodes, {(int)(s + N)}), N, 2 * N);
    rep(i, N) {
        if (res[i] >= INF) res[i] = -1;
    }
    print(res);
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
