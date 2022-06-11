/*
・きっちり自力AC！
・setにpair<char,char>で置換できる条件詰める。
　set乗るけど雑に2乗で通ると信じて投げる。
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

#include "common/HashSet.hpp"

class Solution {
public:
    bool matchReplacement(string S, string sub, vector<vector<char>>& mappings) {
        ll N = S.size();
        ll K = sub.size();
        ll M = mappings.size();
        HashSet<pair<char, char>> se;
        rep(i, M) {
            se.insert({mappings[i][0], mappings[i][1]});
        }
        rep(i, N-K+1) {
            auto tmp = se;
            bool ok = true;
            rep(j, K) {
                if (S[i+j] != sub[j]) {
                    if (not se.count({sub[j], S[i+j]})) {
                        ok = false;
                        break;
                    }
                }
            }
            if (ok) {
                return true;
            }
        }
        return false;
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
