/*
参考：https://twitter.com/stoq_/status/1502641229317967874
　　　https://atcoder.jp/contests/abc243/submissions/30066882
・別解。ダイクストラ方針。stoqさんより。
・ダイクストラ応用
・全頂点からダイクストラでもN*Mlogくらいなので大丈夫。
　それで、この時最短経路の通り数も持っておく。
　するとダイクストラの後で、全ての辺について、
　その辺が唯一の最短路として使われているかどうかをチェックできる。
　このチェックはダイクストラとは並列な位置で処理するので計算量オーダーは増えない。
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

// ダイクストラ(最短路の通り数付)
template<typename T>
pair<vector<T>, vector<ll>> dijkstra(const vector<vector<pair<ll, T>>> &nodes, int src, int goal=-1) {

    int N = nodes.size();
    vector<T> res(N, INF);
    // 最短ルートの通り数
    vector<ll> cnt(N);
    priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que;
    res[src] = 0;
    cnt[src] = 1;
    que.push({0, src});

    while (!que.empty()) {
        auto [dist, u] = que.top(); que.pop();
        // if (u == goal) return res;
        if (res[u] < dist) continue;
        for (auto [v, cost] : nodes[u]) {
            if (chmin(res[v], dist+cost)) {
                cnt[v] = cnt[u];
                que.push({dist+cost, v});
            } elif (res[v] == dist+cost) {
                cnt[v] += cnt[u];
            }
        }
    }
    return {res, cnt};
}

void solve() {
    ll N, M;
    cin >> N >> M;
    auto G = list2d(N, N, INF);
    vvpll nodes(N);
    vector<array<ll, 3>> edges;
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
        edges.pb({u, v, c});
    }

    set<pll> need;
    rep(s, N) {
        auto [dist, cnt] = dijkstra(nodes, s);
        for (auto [u, v, c] : edges) {
            // 頂点u->vの経路でこの辺が唯一の最短路なら必要
            if (dist[u]+c == dist[v] and cnt[v] == 1) {
                need.insert({u, v});
            }
            if (dist[v]+c == dist[u] and cnt[u] == 1) {
                need.insert({u, v});
            }
        }
    }
    ll ans = M - need.size();
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
