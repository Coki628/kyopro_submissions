/*
・きっちり自力AC！
・累積和取ってにぶたん。境界とかintのオーバーフローとかしょうもないので時間食った…。
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
    long long countSubarrays(const vector<int>& nums, long long K) {
        ll N = nums.size();
        Accumulate<ll> acc(N);
        rep(i, N) acc.set(i, nums[i]);
        acc.build();
        ll ans = 0;
        rep(i, N) {
            ll j = bisearch_max(i, N+1, [&](ll m) {
                return acc.query(i, m)*(ll)(m-i) < K;
            });
            ans += j - i;
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        // auto res = sol.countSubarrays({2,1,4,3,5}, 10);
        auto res = sol.countSubarrays({9,5,3,8,4,7,2,7,4,5,4,9,1,4,8,10,8,10,4,7}, 4);
        print(res);
        return 0;
    }
#endif
