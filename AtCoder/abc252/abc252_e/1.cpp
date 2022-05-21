/*
・きっちり自力AC！
・MSTやるだけ？な訳はない。。頂点1からのって書いてある。ダイクストラして使った辺で全域木。
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
using mint = ModInt<MOD>;
#include "template.hpp"

template<typename T>
vector<pii> dijkstra(const vector<vector<pair<int, T>>> &nodes, int src, int goal=-1) {
    int N = nodes.size();
    vector<T> res(N, INF);
    priority_queue<tuple<T, int, int>, vector<tuple<T, int, int>>, greater<tuple<T, int, int>>> que;
    res[src] = 0;
    que.push({0, src, -1});

    vector<pii> edges;
    while (!que.empty()) {
        auto [dist, u, prv] = que.top(); que.pop();
        if (res[u] < dist) continue;
        if (prv != -1) {
            edges.eb(prv, u);
        }
        for (auto [v, cost] : nodes[u]) {
            if (chmin(res[v], dist+cost)) {
                que.push({dist+cost, v, u});
            }
        }
    }
    return edges;
}

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpil nodes(N);
    map<pii, int> mp;
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
        mp[{u, v}] = i;
        mp[{v, u}] = i;
    }

    auto res = dijkstra(nodes, 0);
    vector<ll> ans;
    for (auto [u, v] : res) {
        ans.eb(mp[{u, v}]+1);
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
