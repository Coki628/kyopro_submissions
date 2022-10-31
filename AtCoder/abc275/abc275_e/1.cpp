/*
・きっちり自力AC！
・確率DP
・制約的に愚直に2乗DPでOK。遷移先がM個あるのでMで割る。
　念のためlogを落とせるので1/Mは前計算しておいた。(やんなくても多分通るけど)
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

    mint invM = (mint)1 / M;
    auto dp = listnd(K+1, N+1, (mint)0);
    dp[0][0] = 1;
    rep(i, K) {
        rep(j, N) {
            rep(k, 1, M+1) {
                ll nxt = j+k <= N ? j+k : N-((j+k)-N);
                dp[i+1][nxt] += dp[i][j] * invM;
            }
        }
        dp[i+1][N] += dp[i][N];
    }
    mint ans = dp[K][N];
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
