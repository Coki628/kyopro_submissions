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
    int mostFrequent(vector<int>& nums, int key) {
        ll N = nums.size();
        map<ll, ll> mp;
        rep(i, N-1) {
            if (nums[i] == key) {
                mp[nums[i+1]]++;
            }
        }
        ll ans = -1, mx = -INF;
        for (auto [k, v] : mp) {
            if (v > mx) {
                mx = v;
                ans = k;
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
