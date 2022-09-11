/*
・きっちり自力AC！
・LIS応用、in-place DP
・LISをにぶたんじゃなくてセグ木でやる方で考えると、遷移の
　seg.query(0, A[i])+1 みたいのを
　seg.query(A[i]-K, A[i])+1 とすれば今回の題意に合う。
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
    int lengthOfLIS(vector<int>& A, int K) {
        ll N = A.size();
        auto seg = get_segment_tree(100007, [](ll a, ll b) { return max(a, b); }, -INF);
        seg.build();
        rep(i, N) {
            seg.update(A[i], max(seg.query(max(A[i]-K, 0), A[i])+1, 1LL));
        }
        ll ans = seg.all();
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
