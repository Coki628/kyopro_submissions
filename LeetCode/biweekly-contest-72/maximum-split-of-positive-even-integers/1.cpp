/*
・きっちり自力AC！
・偶数は必須だとして、追加する値を2ずつ大きくして、
　和が足りなくなった所で最後の要素に残り全部充てて帳尻合わせればいい。
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
    vector<long long> maximumEvenSplit(long long finalSum) {
        if (finalSum%2 != 0) {
            return {};
        }
        ll cur = finalSum;
        vector<ll> ans;
        ll need = 2;
        while (cur >= need) {
            ans.eb(need);
            cur -= need;
            need += 2;
        }
        ans.back() += cur;
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
