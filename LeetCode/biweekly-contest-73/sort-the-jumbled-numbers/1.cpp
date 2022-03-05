/*
・きっちり自力AC
・数値文字列変換しまくる。Pythonだと楽そう。最後はソート。
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
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        ll N = nums.size();
        vector<string> S(N);
        rep(i, N) {
            S[i] = tostr(nums[i]);
        }
        rep(i, N) {
            rep(j, S[i].size()) {
                S[i][j] = tochar(mapping[toint(S[i][j])]);
            }
        }
        vector<pll> converted(N);
        rep(i, N) {
            converted[i] = {toint(S[i]), i};
        }
        sort(ALL(converted));
        vector<int> ans(N);
        rep(i, N) {
            ans[i] = nums[converted[i].second];
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
