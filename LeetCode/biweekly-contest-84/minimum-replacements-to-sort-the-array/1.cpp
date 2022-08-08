/*
・自力AC！
・後ろから貪欲。なるべく平たく割り振れるように、考えて割り算する。
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
    long long minimumReplacement(vector<int> A) {
        ll N = A.size();
        ll ans  = 0;
        rep(i, N-2, -1, -1) {
            if (A[i] > A[i+1]) {
                int cnt = ceil(A[i], A[i+1]);
                ans += cnt - 1;
                A[i] /= cnt;
            }
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        // auto res = sol.minimumReplacement({12,9,7,6,17,19,21});
        auto res = sol.minimumReplacement({7,6,15,6,11,14,10});
        print(res);
        return 0;
    }
#endif
