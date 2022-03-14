/*
参考：https://atcoder.jp/contests/abc243/editorial
・圧倒的ワーシャルフロイドみを感じながらも解けず。。
・ワーシャルフロイド応用
・ある辺が要るかどうか、別の頂点を経由して迂回するのを全探索する。
　辺(u,v)を迂回してもc以下のコストで到達できるなら要らない。
・ABCで出たWFちょい捻ったやつ、前も落としたんだよな…。
　中の仕組みの理解が足りてないんだな、分かって気でいても。
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

#include "graph/warshall_floyd.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    auto G = list2d(N, N, INF);
    vector<array<ll, 3>> edges;
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        G[u][v] = c;
        G[v][u] = c;
        edges.pb({u, v, c});
    }

    auto need = [](vvl& G, ll u, ll v, ll c) {
        ll N = G.size();
        rep(i, N) {
            if (i == u or i == v) continue;
            // 辺(u,v)を迂回してもc以下のコストで到達できるなら要らない
            if (G[u][i]+G[i][v] <= c) {
                return false;
            }
        }
        return true;
    };
    auto wf = warshall_floyd(G);
    ll ans = 0;
    for (auto [u, v, c] : edges) {
        if (not need(wf, u, v, c)) {
            ans++;
        }
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
