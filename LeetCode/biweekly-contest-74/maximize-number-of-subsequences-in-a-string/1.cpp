/*
・きっちり自力AC！
・(連続しない)部分列
・結局、先頭にT[0]か末尾にT[1]を付けるのが最善なので両方試す。
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
    long long maximumSubsequenceCount(string S, string T) {
        ll N = S.size();
        ll ans1 = 0, ans2 = 0;
        string S2 = T[0] + S;
        ll cnt = 0;
        rep(i, N+1) {
            if (S2[i] == T[1]) {
                ans1 += cnt;
            }
            if (S2[i] == T[0]) {
                cnt++;
            }
        }
        S2 = S + T[1];
        cnt = 0;
        rep(i, N+1) {
            if (S2[i] == T[1]) {
                ans2 += cnt;
            }
            if (S2[i] == T[0]) {
                cnt++;
            }
        }
        return max(ans1, ans2);
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
