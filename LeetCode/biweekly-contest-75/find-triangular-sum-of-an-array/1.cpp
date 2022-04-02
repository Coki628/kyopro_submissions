/*
・さくっと自力AC。
・パスカルみたいなやつ。
　10万とかなら二項係数使って寄与みたいになると思うけど、
　2乗効く制約なので、シミュればいい。
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
#include "template.hpp"

class Solution {
public:
    int triangularSum(const vector<int>& A) {
        int N = A.size();
        auto cur = A;
        rep(i, N-1) {
            vector<int> nxt;
            rep(j, cur.size()-1) {
                nxt.eb((cur[j]+cur[j+1])%10);
            }
            cur = nxt;
        }
        return cur[0];
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.triangularSum({2,6,6,5,5,3,3,8,6,4,3,3,5,1,0,1,3,6,9});
        print(res);
        return 0;
    }
#endif
