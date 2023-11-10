/*
・重み付き一般グラフ、最短経路、経路復元
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

#include "graph/get_route.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpil nodes(N);
    rep(i, M) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        nodes[a].eb(b, c);
        nodes[b].eb(a, c);
    }

    vector<int> prv(N, -1);
    auto dijkstra = [&](const vvpil &nodes, const vector<int> &src, int goal = -1) {
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
                    prv[v] = u;
                    que.push({dist + cost, v});
                }
            }
        }
        return res;
    };
    dijkstra(nodes, {0});
    auto res = get_route(prv, 0, N - 1);
    res++;
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
