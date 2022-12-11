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
    int maximumValue(vector<string> &S) {
        int ans = 0;
        for (auto s : S) {
            bool isnum = true;
            for (auto c : s) {
                if (not isdigit(c)) {
                    isnum = false;
                    break;
                }
            }
            if (isnum) {
                chmax(ans, (int)toint(s));
            } else {
                chmax(ans, (int)s.size());
            }
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
