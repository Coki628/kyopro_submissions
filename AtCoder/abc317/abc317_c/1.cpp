/*
・きっちり自力AC！
・順列全探索。グラフは隣接行列で持っとく。
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
    auto G = listnd(N, N, INF);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        G[u][v] = c;
        G[v][u] = c;
    }

    vector<ll> P(N);
    iota(ALL(P), 0);
    ll ans = -INF;
    for (auto &perm : permutations(P)) {
        ll dist = 0;
        rep(i, N - 1) {
            ll u = perm[i];
            ll v = perm[i + 1];
            if (G[u][v] == INF) {
                chmax(ans, dist);
                break;
            }
            dist += G[u][v];
        }
        chmax(ans, dist);
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
