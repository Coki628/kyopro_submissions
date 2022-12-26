/*
・なんとか自力AC！
・共通のやつLCMしたりで整えて、割り算するとx以下で使えない個数とか特定できるので、
　これで片方しか使えないやつ使い切ったりしてから残りで足りる？みたいな判定をにぶたんする。
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
    int minimizeSet(int d1, int d2, int N, int M) {
        ll l = lcm<ll>(d1, d2);
        ll res = bisearch_min(N + M - 1, INF, [&](ll x) {
            ll cnt1 = x / d1;
            ll cnt2 = x / d2;
            ll cntl = x / l;
            ll cnt1uq = cnt1 - cntl;
            ll cnt2uq = cnt2 - cntl;
            ll use1 = min(cnt1uq, (ll)M);
            ll use2 = min(cnt2uq, (ll)N);
            ll rest1 = N - use2;
            ll rest2 = M - use1;
            return rest1 + rest2 <= x - cnt1uq - cnt2uq - cntl;
        });
        assert(res < MOD * 2);
        return (int)res;
    }
};

#ifdef __LOCAL
int main() {
    Solution sol;
    auto res = sol.minimizeSet(2, 4, 8, 2);
    print(res);
    return 0;
}
#endif
