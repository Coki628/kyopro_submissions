/*
・なんとか時間内自力AC！終了30秒前のブザービート。
・前見てそれと合うやつで後ろに近いやつをスワップして持ってった。(未証明…)
　実装はこれも2乗効くので陽に雑にでOK。
　真ん中になるやつの処理は悩んだ。結局、1つ後ろに回して先延ばし、でよかった。
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
    int minMovesToMakePalindrome(string S) {
        ll N = S.size();
        ll cnt = 0;
        rep(i, N/2) {
            ll ii = N-i-1;
            ll j = ii;
            while (S[i] != S[j]) {
                j--;
            }
            if (i == j) {
                swap(S[i], S[i+1]);
                cnt++;
                i--;
            } else {
                rep(k, j, ii) {
                    swap(S[k], S[k+1]);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.minMovesToMakePalindrome("skwhhaaunskegmdtutlgtteunmuuludii");
        print(res);
        return 0;
    }
#endif
