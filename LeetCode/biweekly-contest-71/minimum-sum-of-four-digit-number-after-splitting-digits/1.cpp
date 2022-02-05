/*
・自力AC。ちょいもたついたかも。
・順列と区切り位置全探索したけど、もっと簡単にできた気がする。。
　りとこはこういう文字列操作系好きだなぁ。
*/

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
    int minimumSum(int num) {
        auto tmp = tostr(num);
        vector<char> V(ALL(tmp));
        ll N = V.size();
        
        ll ans = INF;
        for (auto perm : permutations(V)) {
            string S(ALL(perm));
            rep(i, 1, N) {
                ll num1 = toint(S.substr(0, i));
                ll num2 = toint(S.substr(i));
                chmin(ans, num1+num2);
            }
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        int input = 1234;
        Solution sol;
        auto res = sol.minimumSum(input);
        print(res);
        return 0;
    }
#endif
