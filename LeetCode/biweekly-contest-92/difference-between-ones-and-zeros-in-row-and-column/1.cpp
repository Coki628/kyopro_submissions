/*
・自力AC！
・4方向累積取っとく。地味にめんどいやつ。
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

class Solution {
public:
    vector<vector<int>> onesMinusZeros(const vector<vector<int>>& grid) {
        ll H = grid.size();
        ll W = grid[0].size();
        auto acc = listnd(4, H, W, 0);
        rep(h, H) {
            rep(w, W-1) {
                acc[0][h][w+1] = acc[0][h][w] + grid[h][w];
            }
            rep(w, W-1, 0, -1) {
                acc[1][h][w-1] = acc[1][h][w] + grid[h][w];
            }
        }
        rep(w, W) {
            rep(h, H-1) {
                acc[2][h+1][w] = acc[2][h][w] + grid[h][w];
            }
            rep(h, H-1, 0, -1) {
                acc[3][h-1][w] = acc[3][h][w] + grid[h][w];
            }
        }

        auto ans = listnd(H, W, 0);
        int total = H + W - 2;
        rep(h, H) {
            rep(w, W) {
                int cnt1 = acc[0][h][w] + acc[1][h][w] + acc[2][h][w] + acc[3][h][w];
                int cnt0 = total - cnt1;
                ans[h][w] = cnt1 - cnt0 + (grid[h][w] ? 2 : -2);
            }
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.onesMinusZeros({{0,1,1},{1,0,1},{0,0,1}});
        // print(res);
        return 0;
    }
#endif
