/*
・二分探索、最大値の最小化
・行きは飛べるだけ飛んで帰りに届く足場があればOK(だと信じる)。
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
    int maxJump(vector<int> &A) {
        int N = A.size();
        int res = bisearch_min(0, MOD, [&](int x) {
            vector<int> used(N);
            int i = 0;
            while (i < N - 1) {
                int j = bisect_right(A, A[i] + x) - 1;
                if (j == i) {
                    return false;
                }
                used[j] = true;
                i = j;
            }
            while (i > 0) {
                int j = i - 1;
                while (used[j]) {
                    j--;
                }
                int dist = A[i] - A[j];
                if (dist > x) {
                    return false;
                }
                i = j;
            }
            return true;
        });
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
