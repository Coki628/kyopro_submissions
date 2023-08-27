/*
・きっちり自力AC！
・Nとsum(Z)の小ささからそれらを添字に取るDPを考えると、
　その地区の議席を取る/取らなくていいの遷移で行けそうだねとなる。
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
    ll N;
    cin >> N;
    vector<ll> X(N), Y(N), Z(N);
    ll M = 0;
    rep(i, N) {
        cin >> X[i] >> Y[i] >> Z[i];
        M += Z[i];
    }

    auto dp = listnd(N + 1, M + 1, INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, M + 1) {
            if (dp[i][j] == INF) continue;
            assert(X[i] != Y[i]);
            if (X[i] > Y[i]) {
                chmin(dp[i + 1][j + Z[i]], dp[i][j]);
            } else {
                ll need = ceil(Y[i] - X[i], 2LL);
                chmin(dp[i + 1][j], dp[i][j]);
                chmin(dp[i + 1][j + Z[i]], dp[i][j] + need);
            }
        }
    }
    ll ans = INF;
    rep(j, ceil(M, 2LL), M + 1) {
        if (dp[N][j] != INF) {
            chmin(ans, dp[N][j]);
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
