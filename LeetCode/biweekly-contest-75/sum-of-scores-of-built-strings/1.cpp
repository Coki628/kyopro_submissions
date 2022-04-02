/*
・さくっと自力AC。
・LCPって(本当に)書いてある。ロリハをぺたり。
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

#include "string/RollingHash.hpp"

class Solution {
public:
    long long sumScores(const string& S) {
        ll N = S.size();
        RollingHash rh;
        auto table = rh.build(S);
        ll ans = 0;
        rep(i, N) {
            ans += rh.lcp(table, 0, N, table, i, N);
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
