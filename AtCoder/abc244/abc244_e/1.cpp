/*
・きっちり自力AC！
・制約が2乗DPって言ってる。K回の移動とN個の今いる頂点、そこにXの偶奇も持たせればOK。
　遷移はO(N)かかりそうに見えて、実は大丈夫なやつ。
　全部の頂点からM本の辺が出てるってことはあり得ないから。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, M, K, S, T, X;
    cin >> N >> M >> K >> S >> T >> X;
    S--; T--; X--;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto dp = list3d<mint>(K+1, N, 2, 0);
    dp[0][S][0] = 1;
    rep(i, K) {
        rep(u, N) {
            rep(j, 2) {
                if (dp[i][u][j] == 0) continue;
                for (auto v : nodes[u]) {
                    if (v == X) {
                        dp[i+1][v][1-j] += dp[i][u][j];
                    } else {
                        dp[i+1][v][j] += dp[i][u][j];
                    }
                }
            }
        }
    }
    mint ans = dp[K][T][0];
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
