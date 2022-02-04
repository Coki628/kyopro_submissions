/*
参考：https://www.youtube.com/watch?v=9o4Lbxd3up4
・グリッドDP、最短経路、K番目の値
・解説動画の別解。
・何でうまくいくかは解説動画で説明してる棒グラフとか見て欲しい。
　やり方は、決め打ちしたxを予めコストから引いておいて、
　最短路が求まった後でx*Kを固定で追加する感じ。
　この方法でいけば、K番目の値xが実際の値からずれていれば、
　ぴったりの時より解が必ず大きくなるので、全探索すれば最適解が得られる。
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
        auto dp = list2d(H, W, INF);
        dp[0][0] = max(grid[0][0]-a, 0LL);
        rep(i, H) {
            rep(j, W) {
                if (i) {
                    chmin(dp[i][j], dp[i-1][j]+max(grid[i][j]-a, 0LL));
                }
                if (j) {
                    chmin(dp[i][j], dp[i][j-1]+max(grid[i][j]-a, 0LL));
                }
            }
        }
        chmin(ans, dp[H-1][W-1]+a*K);
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
