/*
・自力AC！
・2乗が効くので、2人のいる頂点両方を状態に持ってBFS。
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
    vector<ll> C(N);
    cin >> C;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto dist = listnd(N, N, INF);
    queue<pll> que;
    que.push({0, N - 1});
    dist[0][N - 1] = 0;
    while (que.size()) {
        auto [a, b] = que.front();
        que.pop();
        for (auto u : nodes[a]) {
            for (auto v : nodes[b]) {
                if (C[u] != C[v] and dist[u][v] >= INF) {
                    que.push({u, v});
                    dist[u][v] = dist[a][b] + 1;
                }
            }
        }
    }
    ll ans = dist[N - 1][0];
    if (ans >= INF) ans = -1;
    print(ans);
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
