/*
・自力AC！
・一般グラフ・無向重み付き、最短経路
・ダイクストラ、経路復元、逆辺
・経路復元的なことをする、別のグラフを構築する。
　最短経路が更新されたら、cur<-nxtに有向辺を張って、nxtからの唯一の復元ルートとする。
　タイブレークがあったら、cur<-nxtに有向辺を張って、nxtからの復元ルートを1つ増やす。
　終わったら頂点NからBFSして、これで通れた頂点が答え。
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

#include "graph/bfs.hpp"

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

    vvi nodes2(N);
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
                    nodes2[v].clear();
                    nodes2[v].eb(u);
                    que.push({dist + cost, v});
                } else if (res[v] == dist + cost) {
                    nodes2[v].eb(u);
                }
            }
        }
        return res;
    };
    dijkstra(nodes, {0});

    auto dist = bfs(nodes2, {(int)N - 1});
    ll ans = 0;
    rep(i, N) {
        if (dist[i] < INF) ans++;
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
