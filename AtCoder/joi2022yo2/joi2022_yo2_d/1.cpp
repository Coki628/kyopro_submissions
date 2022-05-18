/*
・部分点3と2。
・1回前と2回前に取った位置を覚えておくDPと、
　直前K個の取ったかの状態をビットで持つDP。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    if (N <= 300) {
        auto dp = list3d(N+1, N+1, N+1, -INF);
        dp[0][N][N] = 0;
        rep(i, N) {
            rep(j, N+1) {
                rep(k, N+1) {
                    chmax(dp[i+1][j][k], dp[i][j][k]);
                    if (k == N or k <= i-K) {
                        chmax(dp[i+1][i][j], dp[i][j][k]+A[i]);
                    }
                }
            }
        }
        ll ans = -INF;
        rep(j, N+1) {
            rep(k, N+1) {
                chmax(ans, dp[N][j][k]);
            }
        }
        print(ans);
    } elif (K <= 10) {
        auto dp = list2d(N+1, 1LL<<K, -INF);
        dp[0][0] = 0;
        rep(i, N) {
            rep(bit, 1LL<<K) {
                chmax(dp[i+1][bit>>1], dp[i][bit]);
                if (popcount(bit>>1) <= 1) {
                    chmax(dp[i+1][(bit>>1)|1LL<<(K-1)], dp[i][bit]+A[i]);
                }
            }
        }
        ll ans = max(dp[N]);
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
