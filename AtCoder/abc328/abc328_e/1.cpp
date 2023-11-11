/*
・なんとか自力AC！時間内危なかった。。
・再帰全探索、全域木
・むずい。辺全部じゃなくて、各頂点で「親へ向かう辺」を選ぶようにすると全探索できる。
　根は親への辺がないので、根をどこにするかは全探索。
　構築したグラフはUFで連結判定してから答えに使う。
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

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vvpil nodes(N);
    vector<array<ll, 3>> edges;
    rep(e, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        nodes[u].pb({e, c});
        nodes[v].pb({e, c});
        edges.pb({u, v, c});
    }

    vector<array<ll, 3>> cur;
    ll ans = INF;
    rep(r, N) {
        vector<int> used(M);
        auto rec = [&](auto&& f, int u, ll sm) {
            if (u == N) {
                UnionFind uf(N);
                rep(e, M) {
                    if (used[e]) {
                        uf.merge(edges[e][0], edges[e][1]);
                    }
                }
                if (uf.size() == 1) {
                    chmin(ans, sm);
                }
                return;
            }
            if (u == r) {
                f(f, u + 1, sm);
            } else {
                for (auto [e, c] : nodes[u]) {
                    if (used[e]) continue;
                    used[e] = true;
                    f(f, u + 1, (sm + c) % K);
                    used[e] = false;
                }
            }
        };
        rec(rec, 0, 0);
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
