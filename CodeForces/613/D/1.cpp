/*
参考：https://smijake3.hatenablog.com/entry/2019/09/15/200200
・ライブラリ整備：Auxiliary Tree
・木DP
・もう1問くらい例題解いとこうと思って。木DPパートも結構むずくて練習になった。
　DP[u][i] := 頂点uの部分木まで見て、その部分木以降に列Aに含まれる頂点がi=0/1/2個以上、の時の最小コスト
　みたいなDPにした。この前やった、遷移元を更新しないようにnxt配列作って
　遷移先の情報を一時的にそっちで保持するやつを早速また使った。
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

#include "graph/AuxiliaryTree.hpp"
#include "common/HashMap.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    AuxiliaryTree aux(nodes);
    ll Q;
    cin >> Q;
    vector<bool> need(N);
    rep(_, Q) {
        ll m;
        cin >> m;
        auto A = LIST<int>(m);
        rep(i, m) A[i]--;

        auto nodes2 = aux.build(A);
        HashMap<int, array<ll, 3>> dp;
        rep(i, m) {
            need[A[i]] = true;
        }
        auto dfs = [&](auto&& f, ll u, ll prv) -> void {
            if (need[u]) {
                dp[u][1] = 0;
                dp[u][0] = dp[u][2] = INF;
            } else {
                dp[u][0] = 0;
                dp[u][1] = dp[u][2] = INF;
            }
            for (auto [v, c] : nodes2[u]) {
                if (v == prv) continue;
                f(f, v, u);
                array<ll, 3> nxt = {INF, INF, INF};
                // 何もしない
                chmin(nxt[0], dp[u][0] + dp[v][0]);
                chmin(nxt[1], dp[u][0] + dp[v][1]);
                chmin(nxt[1], dp[u][1] + dp[v][0]);
                chmin(nxt[2], dp[u][1] + dp[v][1]);
                chmin(nxt[2], dp[u][2] + dp[v][0]);
                chmin(nxt[2], dp[u][2] + dp[v][1]);
                // u-v間の頂点を1つ潰す
                if (c >= 2) {
                    chmin(nxt[0], dp[u][0] + dp[v][1] + 1);
                    chmin(nxt[1], dp[u][1] + dp[v][1] + 1);
                    chmin(nxt[2], dp[u][2] + dp[v][1] + 1);
                }
                dp[u] = nxt;
            }
            // 頂点uを潰す
            if (not need[u]) {
                chmin(dp[u][0], dp[u][1] + 1);
                chmin(dp[u][0], dp[u][2] + 1);
            }
        };
        dfs(dfs, A[0], -1);
        ll ans = min(dp[A[0]][0], dp[A[0]][1]);
        if (ans >= INF) ans = -1;
        print(ans);
        rep(i, m) {
            need[A[i]] = false;
        }
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
