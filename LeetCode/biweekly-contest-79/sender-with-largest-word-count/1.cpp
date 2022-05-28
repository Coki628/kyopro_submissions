/*
・きっちり自力AC！
・spaceの数+1個で集計みたいにしてmost_commonする。
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
    string largestWordCount(vector<string>& S, vector<string>& T) {
        map<string, ll> C;
        ll N = S.size();
        rep(i, N) {
            C[T[i]] += count(ALL(S[i]), ' ') + 1;
        }
        auto res = most_common(C);
        return res[0].second;
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
