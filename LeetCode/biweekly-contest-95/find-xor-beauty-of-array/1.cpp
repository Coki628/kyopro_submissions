/*
・きっちり自力AC！
・ビット毎に見る。立ってる数数えて組み合わせ。
　題意の演算で1になる通り数を求めて奇数ならそのビットは残る。
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
    int xorBeauty(const vector<int> &A) {
        int N = A.size();
        const int L = 30;
        int ans = 0;
        rep(b, L) {
            ll cnt1 = 0;
            rep(i, N) {
                if (A[i] >> b & 1) {
                    cnt1++;
                }
            }
            ll cnt0 = N - cnt1;
            ll p1 = cnt0 * cnt1 * 2 + cnt1 * cnt1;
            ll t1 = p1 * cnt1;
            if (t1 % 2 == 1) {
                ans += 1 << b;
            }
        }
        return ans;
    }
};

#ifdef __LOCAL
int main() {
    Solution sol;
    // auto res = sol.xorBeauty({1,4});
    auto res = sol.xorBeauty({38, 42, 42, 13, 18, 30, 3, 41, 40, 15});
    print(res);
    return 0;
}
#endif
