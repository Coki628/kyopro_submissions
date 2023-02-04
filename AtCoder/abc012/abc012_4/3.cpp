/*
・ライブラリ整備：ワーシャルフロイド
・無向辺ならループ半分で定数倍改善できないかな？と思ってやってみた。
　多分できた。31回ワーシャルフロイドやるコードで、1.03秒→0.80秒くらい。
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

// template<typename T>
// vector<vector<T>> warshall_floyd(vector<vector<T>> G) {
//     ll N = G.size();
//     rep(i, N) G[i][i] = 0;
//     rep(k, N) {
//         rep(i, N) {
//             rep(j, N) {
//                 chmin(G[i][j], G[i][k] + G[k][j]);
//             }
//         }
//     }
//     rep(i, N) {
//         if (G[i][i] < 0) {
//             return {};
//         }
//     }
//     return G;
// }

template<typename T>
vector<vector<T>> warshall_floyd(vector<vector<T>> G) {
    ll N = G.size();
    rep(i, N) G[i][i] = 0;
    rep(k, N) {
        rep(i, N) {
            rep(j, i + 1, N) {
                chmin(G[i][j], G[i][k] + G[k][j]);
                chmin(G[j][i], G[j][k] + G[k][i]);
            }
        }
    }
    rep(i, N) {
        if (G[i][i] < 0) {
            return {};
        }
    }
    return G;
}

void solve() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;
    auto G = listnd(N, N, INF);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        G[u][v] = c;
        G[v][u] = c;
    }

    auto wf = warshall_floyd(G);
    rep(i, 30) warshall_floyd(G);
    ll ans = INF;
    rep(i, N) {
        chmin(ans, max(wf[i]));
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
