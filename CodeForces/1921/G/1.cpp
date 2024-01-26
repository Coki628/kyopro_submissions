/*
・ここでWAになるケースの確認とかしてた。
　全部WAがなくなったらMLE。
　llを全部intにしたけど、変わらずMLE…。
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

#include "grid/flip.hpp"
#include "datastructure/Accumulate2D.hpp"

// 493.#..#..##......###.#.....##.##.#..##

// 1031####..#....#.....#.#.#.#..###.

void solve(int t) {
    int H, W, K;
    cin >> H >> W >> K;
    K++;
    vector<string> grid(H + K * 2, string(W + K * 2, '.'));
    rep(h, K, K + H) {
        cin >> grid[h];
        grid[h] = string(K, '.') + grid[h] + string(K, '.');
    }

    // if (t == 823) {
    //     cout << H << W << --K;
    //     rep(h, K, K + H) {
    //         rep(w, K, K + W) {
    //             cout << grid[h][w];
    //         }
    //     }
    //     cout << endl;
    //     return;
    // }

    auto check = [&](const vector<string> &grid) -> int {
        int H = grid.size();
        int W = grid[0].size();
        Accumulate2D<int> acc(H, W);
        auto acc2 = listnd(H + 1, W + 1, 0);
        rep(h, H) {
            rep(w, W) {
                if (grid[h][w] == '#') {
                    acc.set(h, w, 1);
                    acc2[h + 1][w + 1] = 1;
                }
            }
        }
        acc.build();
        rep(h, H + 1) {
            rep(w, W) {
                acc2[h][w + 1] += acc2[h][w];
            }
        }
        // 左上 → 右下
        rep(h, H) {
            rep(w, W) {
                acc2[h + 1][w + 1] += acc2[h][w];
            }
        }

        int res = 0;
        rep(h, H - K + 1) {
            rep(w, W - K + 1) {
                // 三角形(右下) - 三角形(左上) - 長方形(左下)
                chmax(res, acc2[h + K][w + K] - acc2[h][w] - acc.query(h, 0, h + K, w));
            }
        }
        return res;
    };
    int ans = 0;
    chmax(ans, check(grid));
    grid = flip_h(grid);
    chmax(ans, check(grid));
    grid = flip_w(grid);
    chmax(ans, check(grid));
    grid = flip_h(grid);
    chmax(ans, check(grid));
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
    rep(t, T) solve(t);

    return 0;
}
