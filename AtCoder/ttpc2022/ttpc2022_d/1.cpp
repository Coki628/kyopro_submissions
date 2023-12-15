/*
・気まぐれ埋め。やはりグラフ問は楽しい。
・なんとか自力AC！思ったより手こずった…。
・2色塗り分け、パス、木DP、遷移元に影響のある木DP
・初見で dp[u][i] := 頂点u以下見て、更新回数の偶奇がi
　の木DPで解けそうと思って取り組むと、意外と合わない。
　色々試行錯誤して、遷移元を壊してしまっていることに気付く。
　2乗の木DPの時みたいに、遷移前に別配列作ってからやるとOK。
　結構今までもやってそうなのに、意外とこのパターン初めての気がする。
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
    ll N;
    cin >> N;
    auto A = LIST(N);
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto dp = listnd(N, 2, -INF);
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        dp[u][0] = 0;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            // dp[u][0] <- dp[u][0] + dp[v][0]
            // dp[u][0 + 1] <- dp[u][0] + dp[v][1]
            // dp[u][1] <- dp[u][1] + dp[v][0]
            // dp[u][1 + 1] <- dp[u][1] + dp[v][1]

            // そのまま更新してしまうと遷移元を壊してしまうので別配列へ
            auto nxt = dp[u];
            nxt[0] = max(dp[u][0] + dp[v][0], dp[u][1] + dp[v][1]);
            nxt[1] = max(dp[u][0] + dp[v][1], dp[u][1] + dp[v][0]);
            dp[u] = nxt;
        }
        if (prv != -1 and nodes[u].size() == 1) {
            dp[u][0] = A[u];
            dp[u][1] = 1 - A[u];
        } else {
            dp[u][0] += A[u];
            dp[u][1] += 1 - A[u];
        }
    };
    dfs(dfs, 0, -1);
    ll ans = max(dp[0]);
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
