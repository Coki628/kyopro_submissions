/*
・きっちり自力AC！
・やる。こういう文字列⇔数値変換みたいの、りとこ多いよね。
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
    string largestGoodInteger(string S) {
        ll N = S.size();
        string ans;
        ll mx = -INF;
        rep(i, N-2) {
            string s = S.substr(i, 3);
            UNIQUE(s);
            if (s.size() == 1) {
                s = string(3, s[0]);
                if (chmax(mx, toint(s))) {
                    ans = s;
                }
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
