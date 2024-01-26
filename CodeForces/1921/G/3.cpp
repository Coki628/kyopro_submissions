/*
・グリッド広げるのを関数の内側にしてみた。変わらずMLE…。
・この後のはみ出し処理を考えて、基準点が左上にある方が都合が良さそうに思えたので、
　累積和を取る向きを変えた。負方向の累積なので、添字考えるのがつらい。
・なお、flipをrotateに変えてみたりしたけど、特に変化はない。
　4方向網羅できてることに変わりはなさそう。
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

#include "grid/rot90.hpp"
#include "datastructure/Accumulate2D.hpp"

void solve() {
    int H, W, K;
    cin >> H >> W >> K;
    K++;
    vector<string> grid(H);
    cin >> grid;

    auto check = [&](const vector<string> &arg) -> int {
        int H = grid.size();
        int W = grid[0].size();
        bool grid[H + K][W + K] = {};
        rep(h, H) {
            rep(w, W) {
                if (arg[h][w] == '#') {
                    grid[h][w] = true;
                }
            }
        }
        H = H + K;
        W = W + K;

        Accumulate2D<int> acc(H, W);
        auto acc2 = listnd(H + 1, W + 1, 0);
        rep(h, H) {
            rep(w, W) {
                if (grid[h][w]) {
                    acc.set(h, w, 1);
                    acc2[h + 1][w] = 1;
                }
            }
        }
        acc.build();
        rep(h, H) {
            rep(w, W + 1) {
                acc2[h + 1][w] += acc2[h][w];
            }
        }
        // 右上 → 左下
        rep(h, H) {
            rep(w, W, 0, -1) {
                acc2[h + 1][w - 1] += acc2[h][w];
            }
        }

        int res = 0;
        rep(h, H - K + 1) {
            rep(w, W - K + 1) {
                // 三角形(左下) - 三角形(右上) - 長方形(左上)
                chmax(res, acc2[h + K][w] - acc2[h][w + K] - acc.query(0, w, h, w + K));
            }
        }
        return res;
    };
    int ans = 0;
    chmax(ans, check(grid));
    grid = rot90(grid);
    chmax(ans, check(grid));
    grid = rot90(grid);
    chmax(ans, check(grid));
    grid = rot90(grid);
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
    while (T--) solve();

    return 0;
}
