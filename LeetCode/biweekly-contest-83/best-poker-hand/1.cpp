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
    string bestHand(vector<int>& ranks, vector<char>& suits) {
        auto C1 = Counter(suits);
        if (C1.size() == 1) {
            return "Flush";
        }
        auto C2 = Counter(ranks);
        for (auto [k, v] : C2) {
            if (v >= 3) {
                return "Three of a Kind";
            }
        }
        for (auto [k, v] : C2) {
            if (v >= 2) {
                return "Pair";
            }
        }
        return "High Card";
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
