/*
・自力AC！
・最小コスト求めると思って決め打ちにぶたん*プリキューとか書いてた時間が…。
　よく見ると最悪ケースを見つけるなので、トドメを刺すiを全探索とすると、
　(損をする)差分総和-差分i+コストiのchmaxみたいのでいけた。
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
    long long minimumMoney(const vector<vector<int>>& tran) {
        ll N = tran.size();
        ll diffsm = 0;
        vector<ll> diffs(N);
        rep(i, N) {
            diffs[i] = max(tran[i][0]-tran[i][1], 0);
            diffsm += diffs[i];
        }
        ll ans = 0;
        rep(i, N) {
            chmax(ans, diffsm-diffs[i]+tran[i][0]);
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.minimumMoney({{2,1},{5,0},{4,2}});
        print(res);
        return 0;
    }
#endif
