/*
・きっちり自力AC！
・制約が小さい。列でビット全探索した。
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
    int maximumRows(vector<vector<int>>& mat, int K) {
        ll H = mat.size();
        ll W = mat[0].size();
        int ans = 0;
        rep(bit, 1LL<<W) {
            if (popcount(bit) != K) continue;
            vector<int> ok(H, 1);
            rep(h, H) {
                rep(w, W) {
                    if (mat[h][w] and !(bit>>w & 1)) {
                        ok[h] = 0;
                    }
                }
            }
            chmax(ans, sum(ok));
        }
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
