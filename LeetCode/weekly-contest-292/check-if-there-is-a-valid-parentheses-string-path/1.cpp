/*
・自力AC！よくちゃんと間に合った。ラスト1分ブザービート。
　考察～実装全部を10分ちょいでやり切ったのは頑張ったと思う。
　まあ開始30分近くサイト繋がらなかったのがなければ、もっと普通にできたんだけどね…。
・グリッドDP、括弧列のDP
・基本はグリッドDPの形で、括弧列の扱いは「開き括弧を何個ストックしてるか」
　を状態に持てば、適切に進められる。
・多次元vectorの初期化がなぜかTLEになるのは前にもあったから、
　今回も起きたけどすぐグローバルで生配列取って対応した。
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

int dp[107][107][207];

class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        ll H = grid.size();
        ll W = grid[0].size();
        rep(i, H+1) rep(j, W+1) rep(k, H+W+1) dp[i][j][k] = 0;
        dp[1][0][0] = 1;
        dp[0][1][0] = 1;
        rep(i, 1, H+1) {
            rep(j, 1, W+1) {
                rep(k, H+W+1) {
                    if (grid[i-1][j-1] == '(') {
                        if (k+1 <= H+W) {
                            dp[i][j][k+1] |= dp[i][j-1][k];
                            dp[i][j][k+1] |= dp[i-1][j][k];
                        }
                    } else {
                        if (k-1 >= 0) {
                            dp[i][j][k-1] |= dp[i][j-1][k];
                            dp[i][j][k-1] |= dp[i-1][j][k];
                        }
                    }
                }
            }
        }
        bool ans = dp[H][W][0];
        return ans;
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
