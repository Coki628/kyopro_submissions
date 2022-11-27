/*
・2次元累積和ライブラリで殴ったらめっちゃ楽だった。
　せっかく作ってあるんだからさっさとこっちでやれば良かったね。
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

#include "datastructure/Accumulate2D.hpp"

class Solution {
public:
    vector<vector<int>> onesMinusZeros(const vector<vector<int>>& grid) {
        ll H = grid.size();
        ll W = grid[0].size();
        Accumulate2D<int> acc(grid);

        auto ans = listnd(H, W, 0);
        int total = H + W;
        rep(h, H) {
            rep(w, W) {
                int cnt1 = acc.query(h, 0, h+1, W) + acc.query(0, w, H, w+1);
                int cnt0 = total - cnt1;
                ans[h][w] = cnt1 - cnt0;
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
