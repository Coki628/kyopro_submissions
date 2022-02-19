/*
・なんとか自力AC！
・DP高速化
・一方のある値のindexが他方でどこにあるか的なものを配列に持つと、
　前から順に増加列を作っていくDPと見ることができて、
　dp[i][j] := i+1個選んだ状態で、最後に使った値がjとなる通り数
　みたいなやつをBITで貰う遷移高速化すれば10万でも間に合う。
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
    long long goodTriplets(const vector<int>& nums1, const vector<int>& nums2) {
        ll N = nums1.size();
        vector<ll> atoi(N);
        rep(i, N) {
            atoi[nums1[i]] = i;
        }
        vector<ll> A(N);
        rep(i, N) {
            A[i] = atoi[nums2[i]];
        }

        vector<BIT<ll>> dp(3, {(int)N});
        rep(i, N) {
            dp[0].add(A[i], 1);
            dp[1].add(A[i], dp[0].query(0, A[i]));
            dp[2].add(A[i], dp[1].query(0, A[i]));
        }
        ll ans = dp[2].query(0, N);
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.goodTriplets({4,0,1,3,2}, {4,1,0,2,3});
        print(res);
        return 0;
    }
#endif
