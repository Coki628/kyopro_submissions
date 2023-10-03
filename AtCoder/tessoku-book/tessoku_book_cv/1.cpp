/*
・bitDP、TSP
・出発点に戻る、なので添字が1つ多い。計算量きつそうかな、って思ったけど、
　15^2*15*15*15を計算したら1億ちょいなので間に合うと判断して無事AC。
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
    vector<ll> X(N), Y(N);
    rep(i, N) {
        cin >> X[i] >> Y[i];
    }

    auto dist = listnd(N, N, (ld)0);
    rep(i, N) {
        rep(j, i + 1, N) {
            dist[i][j] = dist[j][i] = hypot(X[i] - X[j], Y[i] - Y[j]);
        }
    }

    ld dp[1LL << N][N][N] = {};
    rep(bit, 1LL << N) {
        rep(i, N) {
            rep(j, N) {
                dp[bit][i][j] = INF;
            }
        }
    }
    rep(i, N) {
        dp[1LL << i][i][i] = 0;
    }
    rep(bit, 1LL << N) {
        rep(i, N) {
            if (!(bit >> i & 1)) continue;
            rep(j, N) {
                rep(k, N) {
                    if (bit >> k & 1) continue;
                    chmin(dp[bit | 1LL << k][k][j], dp[bit][i][j] + dist[i][k]);
                }
            }
        }
    }
    ld ans = INF;
    rep(i, N) {
        rep(j, N) {
            if (dp[(1LL << N) - 1][i][j] >= INF) continue;
            chmin(ans, dp[(1LL << N) - 1][i][j] + dist[i][j]);
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
