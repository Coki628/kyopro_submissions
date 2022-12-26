/*
・きっちり自力AC！
・数え上げ、重複度で割る
・Q3より簡単？単語毎に階乗して重複分は割る。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    int countAnagrams(string S) {
        ll N = S.size();
        ModTools<mint> mt(N);
        mint ans = 1;
        for (auto s : split(S, ' ')) {
            ll n = s.size();
            auto C = Counter(s);
            mint cnt = mt.fact(n);
            for (auto [k, v] : C) {
                cnt /= mt.fact(v);
            }
            ans *= cnt;
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
