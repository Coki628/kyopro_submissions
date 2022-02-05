// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        ll N = nums.size();
        vector<int> lo, mi, hi;
        rep(i, N) {
            if (nums[i] < pivot) {
                lo.eb(nums[i]);
            } elif (nums[i] == pivot) {
                mi.eb(nums[i]);
            } else {
                hi.eb(nums[i]);
            }
        }
        vector<int> ans;
        for (auto a : lo) ans.eb(a);
        for (auto a : mi) ans.eb(a);
        for (auto a : hi) ans.eb(a);
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        return 0;
    }
#endif
