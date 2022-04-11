/*
・きっちり自力AC。
・DPした。直前にどっち使ったか持つ。
　でも制約が2乗OKだから、しなくてもよかったぽい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vvl V(2);
    V[0] = LIST(N);
    V[1] = LIST(N);

    auto dp = list2d(N, 2, INF);
    dp[0][0] = dp[0][1] = 0;
    rep(i, N-1) {
        rep(j, 2) {
            rep(k, 2) {
                chmin(
                    dp[i+1][k],
                    dp[i][j] + abs(V[j][i]-V[k][i+1]) + abs(V[1-j][i]-V[1-k][i+1])
                );
            }
        }
    }
    ll ans = min(dp[N-1]);
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
