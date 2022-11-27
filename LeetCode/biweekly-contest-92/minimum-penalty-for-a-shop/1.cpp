/*
・きっちり自力AC！
　同じ累積和で解くものとしてはQ2よりこのQ3のが易しくないかね。
・手前のNと先のYを数える。累積取っとけば、高速に全箇所チェックできる。
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
    int bestClosingTime(string S) {
        int N = S.size();
        Accumulate<int> acc1(N), acc2(N);
        rep(i, N) {
            if (S[i] == 'N') {
                acc1.set(i, 1);
            } else {
                acc2.set(i, 1);
            }
        }
        acc1.build();
        acc2.build();
        int mn = MOD, ans = -1;
        rep(i, N+1) {
            if (chmin(mn, acc1.query(0, i)+acc2.query(i, N))) {
                ans = i;
            }
        }
        assert(ans != -1);
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
