/*
・さくっと自力AC！
・りとこ、いつもの文字列⇔数値変換。
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

class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string S = tostr(num);
        ll N = S.size();
        int res = 0;
        rep(i, N-k+1) {
            ll cur = toint(S.substr(i, k));
            if (cur > 0 and num%cur == 0) {
                res++;
            }
        }
        return res;
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
