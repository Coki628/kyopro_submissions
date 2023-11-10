/*
・グラフに帰着、BFS
・ビットの状態を頂点、操作を辺として最短経路取ればOK。
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
    vector<ll> A(N);
    cin >> A;
    ll L = 1LL << N;
    vvi nodes(L);
    rep(i, M) {
        ll x, y, z;
        cin >> x >> y >> z;
        x--, y--, z--;
        rep(u, L) {
            ll v = u;
            v ^= 1LL << x;
            v ^= 1LL << y;
            v ^= 1LL << z;
            nodes[u].eb(v);
        }
    }
    ll s = 0;
    rep(i, N) {
        if (A[i]) {
            s += 1LL << i;
        }
    }
    ll t = (1LL << N) - 1;
    auto dist = bfs(nodes, {(int)s});
    ll ans = dist[t] < INF ? dist[t] : -1;
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
