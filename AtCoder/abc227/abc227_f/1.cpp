/*
参考：https://atcoder.jp/contests/abc227/editorial
・upsolveした。再考したけど自力は無理だった。
・グリッドDP、最短経路、K番目の値
・大きい方からK番目に来る値xが何なのかであり得るものを決め打って全部見る。
　すると、そのうちのどれかは本当にK番目の値なので、
　この時、設定した値xが大きすぎればK個に足りなくなるし、
　小さすぎればK個より多くなってしまうので、状態として通常のグリッドDPに加えて
　「何個和に含めたか」を持っておけば正しい解を得られる。
　(大きすぎればK個の状態まで遷移できなかったり、できても最小値より大きい解になるし、
　小さすぎれば早めにK個まで遷移してしまってグリッドの終点に届かない。多分。)
・今回は同値もあるので、グリッドの値が設定したxと等しい時は、
　どちらもあり得るとして含める含めないの両方の遷移をやるといい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll H, W, K;
    cin >> H >> W >> K;
    auto grid = list2d(H, W, 0LL);
    vector<ll> A;
    rep(i, H) {
        rep(j, W) {
            cin >> grid[i][j];
            A.eb(grid[i][j]);
        }
    }

    ll ans = INF;
    for (auto a : A) {
        auto dp = list3d(H, W, K+2, INF);
        if (grid[0][0] < a) {
            dp[0][0][0] = 0;
        } elif (grid[0][0] > a) {
            dp[0][0][1] = grid[0][0];
        } else {
            dp[0][0][0] = 0;
            dp[0][0][1] = grid[0][0];
        }
        rep(i, H) {
            rep(j, W) {
                rep(k, K+1) {
                    if (i) {
                        if (grid[i][j] < a) {
                            chmin(dp[i][j][k], dp[i-1][j][k]);
                        } elif (grid[i][j] > a) {
                            chmin(dp[i][j][k+1], dp[i-1][j][k]+grid[i][j]);
                        } else {
                            chmin(dp[i][j][k], dp[i-1][j][k]);
                            chmin(dp[i][j][k+1], dp[i-1][j][k]+grid[i][j]);
                        }
                    }
                    if (j) {
                        if (grid[i][j] < a) {
                            chmin(dp[i][j][k], dp[i][j-1][k]);
                        } elif (grid[i][j] > a) {
                            chmin(dp[i][j][k+1], dp[i][j-1][k]+grid[i][j]);
                        } else {
                            chmin(dp[i][j][k], dp[i][j-1][k]);
                            chmin(dp[i][j][k+1], dp[i][j-1][k]+grid[i][j]);
                        }
                    }
                }
            }
        }
        chmin(ans, dp[H-1][W-1][K]);
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
