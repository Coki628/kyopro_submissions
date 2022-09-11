/*
・きっちり自力AC！
・いもすやって最大値。
・なんかりとこがマルチテストケースっぽく動作する気がして、
　念のため座圧したけど、しなくても良かったかもしれない。
　(同じような状況でこの後セグ木要素10万固定で作って通ったので。)
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
    int minGroups(vector<vector<int>>& intervals) {
        ll N = intervals.size();
        Compress<ll> cp;
        rep(i, N) {
            intervals[i][1]++;
            cp.add(intervals[i][0]);
            cp.add(intervals[i][1]);
        }
        cp.build();
        ll M = cp.size();
        vector<ll> imos(M);
        rep(i, N) {
            imos[cp[intervals[i][0]]]++;
            imos[cp[intervals[i][1]]]--;
        }
        rep(i, M-1) {
            imos[i+1] += imos[i];
        }
        ll ans = max(imos);
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
