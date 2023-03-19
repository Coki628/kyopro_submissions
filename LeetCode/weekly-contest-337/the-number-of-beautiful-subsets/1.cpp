/*
・自力AC！
・bitDP、前計算
・bitDPなんだけど内側20*20回すと無理で、前計算してbit同士突き合わす感じにしたら通った。
　なんかTL見てると愚直通ったみたいのも観測したんだけどどうやったんだろー。
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
    int beautifulSubsets(const vector<int> &A, int K) {
        int N = A.size();
        vector<ll> ng(N);
        rep(i, N) {
            rep(j, N) {
                if (abs(A[i] - A[j]) == K) {
                    ng[i] |= 1 << j;
                }
            }
        }

        vector<int> dp(1 << N);
        dp[0] = 1;
        rep(bit, 1 << N) {
            if (!dp[bit]) continue;
            rep(i, N) {
                if (bit >> i & 1) continue;
                int res = bit & ng[i];
                if (res == 0) {
                    dp[bit | (1 << i)] = 1;
                }
            }
        }
        int ans = sum(dp) - 1;
        return ans;
    }
};

#ifdef __LOCAL
int main() {
    Solution sol;
    auto res = sol.beautifulSubsets({1}, 1);
    print(res);
    return 0;
}
#endif
