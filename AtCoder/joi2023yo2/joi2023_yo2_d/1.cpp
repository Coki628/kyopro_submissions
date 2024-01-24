/*
・部分点1,3,4,5、時間内自力はここまで。
・色々状態持ってDP
・部分点5に使ったDPで個数Wの次元あたりを削れれば完答できそうなんだけど、って感じ。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, W, D;
    cin >> N >> W >> D;
    vector<ll> A(N - 1);
    cin >> A;

    if (N <= 15) {
        // 部分点4
        A.insert(A.begin(), 0);
        auto dp = listnd(1LL << N, N, W + 1, INF);
        dp[1][0][0] = 0;
        rep(bit, 1, 1LL << N) {
            rep(i, N) {
                rep(j, W + 1) {
                    // 荷物kを取りに行く
                    rep(k, N) {
                        if (bit >> k & 1) continue;
                        if (j + 1 <= W) {
                            // i -> k
                            chmin(dp[bit | 1LL << k][k][j + 1], dp[bit][i][j] + abs(i - k));
                        }
                        // i -> 0 -> k
                        chmin(dp[bit | 1LL << k][k][1], dp[bit][i][j] + i + k);
                    }
                }
            }
        }
        ll ans = -INF;
        rep(bit, 1, 1LL << N) {
            ll val = 0;
            rep(i, N) {
                if (bit >> i & 1) {
                    val += A[i];
                }
            }
            rep(i, N) {
                rep(j, W + 1) {
                    if (dp[bit][i][j] + i <= D) {
                        chmax(ans, val);
                    }
                }
            }
        }
        print(ans);
    } else if (W == 1) {
        // 部分点1,3
        A.insert(A.begin(), 0);
        auto dp = listnd(N + 1, D + 1, -INF);
        dp[1][0] = 0;
        rep(i, 1, N) {
            rep(j, D + 1) {
                if (dp[i][j] <= -INF) continue;
                chmax(dp[i + 1][j], dp[i][j]);
                if (j + i * 2 <= D) {
                    chmax(dp[i + 1][j + i * 2], dp[i][j] + A[i]);
                }
            }
        }
        ll ans = max(dp[N]);
        print(ans);
    } else if (N <= 50) {
        // 部分点5
        A.insert(A.begin(), 0);
        auto dp = listnd(2, D + 1, W + 1,  2, -INF);
        dp[1][0][0][0] = 0;
        rep(i, 1, N) {
            rep(j, D + 1) {
                rep(k, W + 1) {
                    // 0 -> i + 1
                    if (j + i + 1 <= D) {
                        chmax(dp[(i + 1) % 2][j + i + 1][0][1], dp[i % 2][j][k][0]);
                        chmax(dp[(i + 1) % 2][j + i + 1][1][1], dp[i % 2][j][k][0] + A[i]);
                    }
                    // i -> i + 1
                    if (j + 1 <= D) {
                        chmax(dp[(i + 1) % 2][j + 1][k][1], dp[i % 2][j][k][1]);
                        if (k + 1 <= W) {
                            chmax(dp[(i + 1) % 2][j + 1][k + 1][1], dp[i % 2][j][k][1] + A[i]);
                        }
                    }
                    // i -> 0
                    if (j + i <= D) {
                        chmax(dp[(i + 1) % 2][j + i][0][0], dp[i % 2][j][k][1]);
                        if (k < W) {
                            chmax(dp[(i + 1) % 2][j + i][0][0], dp[i % 2][j][k][1] + A[i]);
                        }
                    }
                    // 0 -> 0
                    chmax(dp[(i + 1) % 2][j][0][0], dp[i % 2][j][k][0]);
                    if (j + i * 2 <= D) {
                        chmax(dp[(i + 1) % 2][j + i * 2][0][0], dp[i % 2][j][k][0] + A[i]);
                    }
                    dp[i % 2][j][k][0] = -INF;
                    dp[i % 2][j][k][1] = -INF;
                }
            }
        }
        ll ans = -INF;
        rep(j, D + 1) {
            rep(k, W + 1) {
                chmax(ans, dp[N % 2][j][k][0]);
            }
        }
        print(ans);
    } else {
        assert(0);
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
