/*
・自力ならず。真剣に取り組む前にTLで本質見ちゃったので。。
・一般グラフ有向重み付き、ウォーク、負辺あり負閉路なし
・ワーシャルフロイド、bitDP、TSP
・ワーシャルフロイドなどで全頂点対の最短距離を求めておけば、後は普通のTSPやるだけ。
　でもこれ時間をかけたとして、この前処理気付けたか？と言われると分からない。
　少なくとも本番中ちょこっと考えただけでは思い至らなかった。
　あとTLでみんなハマってたけど、負辺がある関係でINFが少し小さくなりうるので、
　そういう遷移を徹底的に防ぐか、判定時のINFを少し小さくするかが必要。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "graph/warshall_floyd.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    auto G = listnd(N, N, INF);
    rep(i, M) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        G[u][v] = w;
    }

    auto dist = warshall_floyd(G);
    auto dp = listnd(1LL << N, N, INF);
    rep(i, N) {
        dp[1LL << i][i] = 0;
    }
    rep(bit, 1LL << N) {
        rep(i, N) {
            if (!(bit >> i & 1)) continue;
            if (dp[bit][i] == INF) continue;
            rep(j, N) {
                if (bit >> j & 1) continue;
                if (dist[i][j] == INF) continue;
                chmin(dp[bit | 1LL << j][j], dp[bit][i] + dist[i][j]);
            }
        }
    }
    ll ans = INF;
    rep(i, N) {
        chmin(ans, dp[(1LL << N) - 1][i]);
    }
    if (ans >= INF) {
        No();
    } else {
        print(ans);
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
