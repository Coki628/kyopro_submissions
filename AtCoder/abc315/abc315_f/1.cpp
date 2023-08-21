/*
・自力ならず。
・スキップ最大30くらいでいいの全然気付かなかった…。
　それが分かればまあきっちりDPすれば通る。
　Dよりはこれのが目があったし通せるべきだった。
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

#include "geometry/Point.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<Point<double>> P;
    rep(i, N) {
        double x, y;
        cin >> x >> y;
        P.pb({x, y});
    }

    const int M = 30;
    auto dp = listnd(N, M, (double)INF);
    dp[0][0] = 0;
    rep(i, N - 1) {
        rep(j, M) {
            if (dp[i][j] >= INF) continue;
            chmin(dp[i + 1][j], dp[i][j] + P[i].abs(P[i + 1]));
            rep(k, i + 2, N - 1) {
                if (j + (k - i - 1) >= M) break;
                chmin(dp[k][j + (k - i - 1)], dp[i][j] + P[i].abs(P[k]));
            }
        }
    }
    double ans = dp[N - 1][0];
    rep(j, 1, M) {
        chmin(ans, dp[N - 1][j] + pow(2, j - 1));
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
