/*
・きっちり自力AC！
・ナイトの8方向を準備して愚直シミュ。
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

const vector<pii> dir_knight = {{-2, -1}, {-1, -2}, {2, 1},  {1, 2},
                                {-2, 1},  {-1, 2},  {2, -1}, {1, -2}};

class Solution {
public:
    bool checkValidGrid(vector<vector<int>> &grid) {
        int N = grid.size();
        int ch = 0, cw = 0;
        rep(i, 1, N * N) {
            bool ok = false;
            for (auto [dh, dw] : dir_knight) {
                int nh = ch + dh;
                int nw = cw + dw;
                if (nh < 0 or nw < 0 or nh >= N or nw >= N) continue;
                if (grid[nh][nw] == i) {
                    ok = true;
                    ch = nh;
                    cw = nw;
                    break;
                }
            }
            if (not ok) {
                return false;
            }
        }
        return true;
    }
};

#ifdef __LOCAL
int main() {
    // Solution sol;
    // auto res = sol.funcName();
    // print(res);
    return 0;
}
#endif
