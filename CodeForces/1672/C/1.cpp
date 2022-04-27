/*
・なんとか自力AC。
・いい感じの貪欲みたいのが生えず、
　dp[i番目まで見て][直前に操作してない/した][2回前にしてない/した][隣接が同じになった回数0/1]
　ってDPした…。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    auto dp = list4d(N, 2, 2, 2, INF);
    dp[1][0][0][0] = 0;
    dp[1][1][0][0] = 1;
    rep(i, 1, N-1) {
        rep(j, 2) {
            rep(k, 2) {
                rep(l, 2) {
                    // 直前未操作
                    if (j == 0) {
                        // 2回前の操作kも見る
                        if (A[i-1] == A[i] and k == 0) {
                            if (l+1 < 2) {
                                chmin(dp[i+1][0][j][l+1], dp[i][j][k][l]);
                            }
                            chmin(dp[i+1][1][j][l], dp[i][j][k][l]+1);
                        } else {
                            chmin(dp[i+1][0][j][l], dp[i][j][k][l]);
                            chmin(dp[i+1][1][j][l], dp[i][j][k][l]+1);
                        }
                    // 直前操作
                    } else {
                        // 常にA[i-1] == A[i]
                        if (l+1 < 2) {
                            chmin(dp[i+1][0][j][l+1], dp[i][j][k][l]);
                        }
                        chmin(dp[i+1][1][j][l], dp[i][j][k][l]+1);
                    }
                }
            }
        }
    }
    ll ans = INF;
    rep(j, 2) {
        rep(k, 2) {
            rep(l, 2) {
                ll nxl = A[N-2] == A[N-1] and k == 0 or j == 1 ? l+1 : l;
                if (nxl < 2) {
                    chmin(ans, dp[N-1][j][k][l]);
                }
            }
        }
    }
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
