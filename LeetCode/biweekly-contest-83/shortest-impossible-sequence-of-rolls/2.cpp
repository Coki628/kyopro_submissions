/*
参考：https://leetcode.com/problems/shortest-impossible-sequence-of-rolls/discuss/2322375/Greedy-or-Easy-To-Understand-or-With-Approach
・自力ならず…。
・部分列、貪欲
・例えばK=5で1文字を全種揃えるには1,2,3,4,5が全て出現済である必要があって、
　2文字を全種揃えるには1文字が最後に揃い終わった位置以降から、
　また1,2,3,4,5が全て出現する必要がある。これが一般に言える。
　理解すれば確かにそれはそうだけど、これ気付かなかったなぁ…。
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
    int shortestSequence(vector<int>& rolls, int K) {
        ll N = rolls.size();
        rep(i, N) rolls[i]--;
        
        set<ll> se;
        ll cnt = 0;
        rep(i, N) {
            se.insert(rolls[i]);
            if (se.size() == K) {
                cnt++;
                se.clear();
            }
        }
        return cnt + 1;
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
