/*
・きっちり自力AC！
・指示通り条件を並べる。こういうのC++でやりたくなくなるよね…。
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
    bool strongPasswordCheckerII(string S) {
        ll N = S.size();
        if (N < 8) {
            return false;
        }
        bool ok = false;
        for (auto c : S) {
            if (ascii_lowercase.find(c) != -1) {
                ok = true;
                break;
            }
        }
        if (not ok) {
            return false;
        }
        ok = false;
        for (auto c : S) {
            if (ascii_uppercase.find(c) != -1) {
                ok = true;
                break;
            }
        }
        if (not ok) {
            return false;
        }
        ok = false;
        for (auto c : S) {
            if (isdigit(c)) {
                ok = true;
                break;
            }
        }
        if (not ok) {
            return false;
        }
        string T = "!@#$%^&*()-+";
        ok = false;
        for (auto c : S) {
            if (T.find(c) != -1) {
                ok = true;
                break;
            }
        }
        if (not ok) {
            return false;
        }
        rep(i, N-1) {
            if (S[i] == S[i+1]) {
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
