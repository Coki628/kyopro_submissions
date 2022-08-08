/*
・自力AC！
・最初自由に選べると思ってタイムロス。。区間加算BITで全体引くみたいな横着をやった。
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

#include "segment/BIT2.hpp"

class Solution {
public:
    long long taskSchedulerII(vector<int>& A, int K) {
        ll N = A.size();
        Compress<int> cp(A);
        ll M = cp.size();
        rep(i, N) {
            A[i] = cp[A[i]];
        }
        BIT2<ll> bit(M);
        ll cur = 0;
        rep(i, N) {
            ll wait = bit[A[i]];
            if (wait > 0) {
                bit.add(0, M, -wait);
                cur += wait;
            }
            bit.add(0, M, -1);
            bit.update(A[i], K);
            cur++;
        }
        return cur;
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
