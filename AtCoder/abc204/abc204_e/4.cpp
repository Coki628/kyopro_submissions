/*
・値実数でindex整数の三分探索のverify
・実際の解が整数除算でも、先に実数でやって周辺を探せばいいので、
　元々の整数さぶたんの周辺探す仕組みがそのまま使える。
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

#include "common/trisearch.hpp"

ll calc(ll t, ll c, ll d) {
    auto [i, val] = trisearch_min<ld>(
        t,
        INF,
        [&](ll m) {
            return (m - t) + d / (ld)(m + 1);
        },
        10
    );
    return c + (i - t) + d / (i + 1);
}

// ダイクストラ
template <typename T>
vector<T> dijkstra(vector<vector<pair<ll, T>>> &nodes, int src, vector<ll> &C, vector<ll> &D) {

    int N = nodes.size();
    vector<T> res(N, INF);
    priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que;
    res[src] = 0;
    que.push({0, src});

    while (!que.empty()) {
        auto [dist, u] = que.top();
        que.pop();
        if (res[u] < dist) continue;
        for (auto [v, e] : nodes[u]) {
            ll cost = calc(dist, C[e], D[e]);
            if (dist + cost < res[v]) {
                res[v] = dist + cost;
                que.push({dist + cost, v});
            }
        }
    }
    return res;
}

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpll nodes(N);
    vector<ll> C(M), D(M);
    rep(i, M) {
        ll u, v;
        cin >> u >> v >> C[i] >> D[i];
        u--;
        v--;
        nodes[u].pb({v, i});
        nodes[v].pb({u, i});
    }

    auto res = dijkstra(nodes, 0, C, D);
    if (res[N - 1] >= INF) {
        print(-1);
    } else {
        print(res[N - 1]);
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
