/*
・きっちり自力AC！
・+-valueを自由にできる → mod valueで同一視 として、個数のある限り0から順に使えばOK。
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
    int findSmallestInteger(vector<int> &A, int K) {
        int N = A.size();
        rep(i, N) {
            A[i] = modulo(A[i], K);
        }
        auto C = Counter(A);
        int ans = 0;
        rep(i, N) {
            int j = i % K;
            if (C[j]) {
                C[j]--;
                ans = i + 1;
            } else {
                break;
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
