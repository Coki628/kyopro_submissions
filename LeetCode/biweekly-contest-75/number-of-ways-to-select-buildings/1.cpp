/*
・DPする。i番目まで見て、j個選んで、直前が0,1どっち、みたいな。
　何かTLEして、vectorを生配列にしたら通った。
　高々10万*定数のvector生成が間に合わない訳ないはずなんだけどな…。
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

ll dp[100007][4][2];

class Solution {
public:
    long long numberOfWays(string S) {
        ll N = S.size();
        vector<ll> A(N);
        rep(i, N) A[i] = S[i] - '0';
        // auto dp = list3d(N+1, 4, 2, 0LL);
        rep(i, N+1) rep(j, 4) rep(k, 2) dp[i][j][k] = 0;
        dp[0][0][0] = dp[0][0][1] = 1;
        rep(i, N) {
            rep(j, 4) {
                rep(k, 2) {
                    dp[i+1][j][k] += dp[i][j][k];
                    if (j+1 <= 3 and A[i] != k) {
                        dp[i+1][j+1][A[i]] += dp[i][j][k];
                    }
                }
            }
        }
        ll ans = dp[N][3][0] + dp[N][3][1];
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
