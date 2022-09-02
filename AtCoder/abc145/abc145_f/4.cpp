/*
・dojo set_e_7_5
・結構すんなり自力AC！
・座圧、3乗DP
・操作する時は直前の列と同じにすると考えればノーコストに。
　列数と操作回数と、高さが座圧すると300くらいになるので、この3つを状態に持ってDP。
　1年前くらいにも自力ACしていて、ほぼ同じ方針で解いてたけど、
　多分その時よりは考察も実装も手際よくやれたと思う。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    Compress<ll> cp(concat(A, {0}));
    ll M = cp.size();
    A = cp.zip(A);

    auto dp = listnd(N+1, K+1, M, INF);
    dp[0][0][0] = 0;
    rep(i, N) {
        rep(j, K+1) {
            rep(k, M) {
                if (j < K) {
                    chmin(dp[i+1][j+1][k], dp[i][j][k]);
                }
                ll cost = max(cp.unzip(A[i])-cp.unzip(k), 0LL);
                chmin(dp[i+1][j][A[i]], dp[i][j][k] + cost);
            }
        }
    }
    ll ans = INF;
    rep(j, K+1) {
        rep(k, M) {
            chmin(ans, dp[N][j][k]);
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
