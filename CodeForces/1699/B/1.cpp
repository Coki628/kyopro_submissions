/*
・これは自力WA
・グリッド、構築
・なんかL字4分割みたいなので行ける気がして、
　それベースで何とかしようと頑張ってしまったのが良くなかった…。
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
    ll H, W;
    cin >> H >> W;
    auto grid = list2d(H, W, -1);

    if (H == 2) {
        grid[0][0] = 1;
        grid[1][0] = 0;
        ll w = 1, p = 0;
        while (w < W-1) {
            grid[0][w] = p;
            grid[0][w+1] = p;
            grid[1][w] = 1 - p;
            grid[1][w+1] = 1 - p;
            w += 2;
            p = 1 - p;
        }
        grid[0][W-1] = p;
        grid[1][W-1] = 1 - p;
    } elif (W == 2) {
        grid[0][0] = 1;
        grid[0][1] = 0;
        ll h = 1, p = 0;
        while (h < H-1) {
            grid[h][0] = p;
            grid[h+1][0] = p;
            grid[h][1] = 1 - p;
            grid[h+1][1] = 1 - p;
            h += 2;
            p = 1 - p;
        }
        grid[H-1][0] = p;
        grid[H-1][1] = 1 - p;
    } else {
        ll N = min(H, W);
        ll M = max(H, W);
        rep(i, N/2) {
            rep(j, i+1) {
                grid[j][i] = i % 2;
                grid[i][j] = i % 2;
                grid[H-i-1][j] = 1 - (i % 2);
                grid[H-j-1][i] = 1 - (i % 2);
                grid[j][W-i-1] = 1 - (i % 2);
                grid[i][W-j-1] = 1 - (i % 2);
                grid[H-i-1][W-j-1] = i % 2;
                grid[H-j-1][W-i-1] = i % 2;
            }
        }
        if (H < W) {
            rep(i, N/2) {
                rep(j, N/2, W-N/2) {
                    grid[i][j] = j % 2;
                    grid[H-i-1][j] = 1 - (j % 2);
                }
            }
        }
        if (H > W) {
            rep(i, N/2) {
                rep(j, N/2, H-N/2) {
                    grid[j][i] = j % 2;
                    grid[j][W-i-1] = 1 - (j % 2);
                }
            }
        }
    }
    rep(i, H) print(grid[i]);
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
