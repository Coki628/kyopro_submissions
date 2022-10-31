/*
・きっちり自力AC！
・制約小さいし愚直に2重ループ*判定でN回して計N3乗の全チェックでOK。
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
    vector<string> twoEditWords(vector<string>& qs, vector<string>& dic) {
        ll N = qs[0].size();
        auto check = [&](string& S, string& T) -> bool {
            ll cnt = 0;
            rep(i, N) {
                cnt += S[i] == T[i];
            }
            return cnt >= N - 2;
        };

        vector<string> ans;
        for (auto& s : qs) {
            for (auto& t : dic) {
                if (check(s, t)) {
                    ans.eb(s);
                    break;
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
