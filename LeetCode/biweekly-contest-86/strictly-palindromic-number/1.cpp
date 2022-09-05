/*
・自力AC。
・これほぼ全部falseなんじゃない？
　って思いながら愚直やって打ち切るようにしたらそれで通った。。
・終了後TLからの情報によると、全falseでOKだったらしい…。
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

#include "numbers/dton.hpp"
#include "string/is_palindrome.hpp"

class Solution {
public:
    bool isStrictlyPalindromic(int N) {
        rep(i, 2, N-1) {
            string s = dton(N, i);
            if (not is_palindrome(s)) {
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
