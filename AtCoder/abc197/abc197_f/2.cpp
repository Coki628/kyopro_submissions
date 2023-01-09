/*
・グラフ、回文、BFS
・こどふぉで類題(1771D)をやったので復習してみた。
　向こうは回文の真ん中から貰うDPで広げていくイメージだったけど、
　こちらは端点が決まっているので、外側から中央に向かって配るDP(BFS)で狭めていく感じ。
　遷移に辺の2重ループ回して計算量大丈夫か心配だったけど、余裕で速くてAC。
・当時は先に辺全部作ってからダイクストラに流し込んだみたいだけど、
　こうやって頂点ペアを状態に持ってBFS書く方がすっきりしてるように思った。
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
    vector<vector<pair<int, char>>> nodes(N);
    rep(i, M) {
        ll u, v;
        char c;
        cin >> u >> v >> c;
        u--, v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
    }

    auto dp = listnd(N, N, INF);
    dp[0][N - 1] = 0;
    ll ans = INF;
    queue<pll> que;
    que.push({0, N - 1});
    while (que.size()) {
        auto [u, v] = que.front();
        que.pop();
        for (auto [nxu, c1] : nodes[u]) {
            for (auto [nxv, c2] : nodes[v]) {
                if (dp[nxu][nxv] < INF) continue;
                if (nxu == v and nxv == u) {
                    // 奇数長の回文になる
                    chmin(ans, dp[u][v] * 2 + 1);
                } else if (c1 == c2) {
                    if (nxu == nxv) {
                        // 偶数長の回文になる
                        chmin(ans, dp[u][v] * 2 + 2);
                    } else {
                        // まだ繋がらないけど継続できるので次へ
                        dp[nxu][nxv] = dp[u][v] + 1;
                        que.push({nxu, nxv});
                    }
                }
            }
        }
    }
    if (ans == INF) ans = -1;
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
