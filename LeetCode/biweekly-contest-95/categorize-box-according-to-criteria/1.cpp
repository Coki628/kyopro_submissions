/*
・書いてある通りにやる。intそのまま掛け算しちゃって1ペナ…。
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
    string categorizeBox(int length, int width, int height, int mass) {
        bool is_bulky = (
            length >= 10000 or width >= 10000 or height >= 10000
            or (ll)length * (ll)width * (ll)height >= 1000000000
        );
        bool is_heavy = mass >= 100;
        if (is_bulky and is_heavy) {
            return "Both";
        } else if (is_bulky) {
            return "Bulky";
        } else if (is_heavy) {
            return "Heavy";
        } else {
            return "Neither";
        }
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
