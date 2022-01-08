/*
・自力AC！
・回文系
・ちょっと悩んだけど、文字列は全て2文字なので、
　前後逆のやつとなるべく多くペアを作ればOK。
　同じ文字2文字は場合分けする。あと回文の真ん中に来るやつも。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        ll N = words.size();
        auto C = Counter(words);
        set<string> used;
        bool has_center = false;
        ll ans = 0;
        for (auto [s, v] : C) {
            if (s[0] == s[1]) {
                ans += v-v%2;
                if (v%2 == 1) {
                    has_center = true;
                }
            } elif (not used.count(s)) {
                auto rev = s;
                swap(rev[0], rev[1]);
                ans += min(v, C[rev])*2;
                used.insert(rev);
            }
        }
        ans += has_center;
        ans *= 2;
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        vector<string> input = {"dd","aa","bb","dd","aa","dd","bb","dd","aa","cc","bb","cc","dd","cc"};
        Solution sol;
        auto res = sol.longestPalindrome(input);
        print(res);
        return 0;
    }
#endif
