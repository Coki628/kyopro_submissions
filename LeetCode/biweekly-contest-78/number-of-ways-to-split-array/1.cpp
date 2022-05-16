/*
・さくっと自力AC！
・累積和
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
using mint = ModInt<MOD>;
#include "template.hpp"

class Solution {
public:
    int waysToSplitArray(vector<int>& A) {
        ll N = A.size();
        vector<ll> tmp(N);
        rep(i, N) tmp[i] = A[i];
        Accumulate<ll> acc(tmp);
        int res = 0;
        rep(i, N-1) {
            ll sm1 = acc.query(0, i+1);
            ll sm2 = acc.query(i+1, N);
            if (sm1 >= sm2) {
                res++;
            }
        }
        return res;
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
