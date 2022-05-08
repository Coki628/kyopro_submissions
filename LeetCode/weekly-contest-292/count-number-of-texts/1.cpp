/*
・きっちり自力AC！
・数え上げDP
・1回の遷移で文字を1字決めるものとして、ボタンを押した回数だけ先に遷移させる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define CAST_MINT_TO_LL
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
    int countTexts(string S) {
        ll N = S.size();
        vector<mint> dp(N+1);
        dp[0] = 1;
        rep(i, N) {
            ll j = i;
            while (j < i+3 and j < N and S[j] == S[i]) {
                dp[j+1] += dp[i];
                j++;
            }
            if (j < N and S[j] == S[i] and (S[j] == '7' or S[j] == '9')) {
                dp[j+1] += dp[i];
            }
        }
        int ans = dp[N];
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
