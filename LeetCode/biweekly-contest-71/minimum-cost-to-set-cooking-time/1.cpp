/*
・自力AC！こういう時間管理でmod 60する系はだいたい実装だるいのになるよね。
・候補として使える時間は1～9999全探索して秒に変換、targetと一致すれば使う、とした。
　leading zeroは明らかに特しなそうなので全部外した。
　後はそれぞれ貪欲っぽく操作して最小取れば良し。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

ll mstosec(ll m, ll s) {
    return m*60+s;
}

class Solution {
public:
    int minCostSetTime(int startAt, int moveCost, int pushCost, int target) {
        
        vector<string> cand;
        rep(i, 1, 10000) {
            auto s = zfill(tostr(i), 4);
            if (target == mstosec(toint(s.substr(0, 2)), toint(s.substr(2)))) {
                reverse(ALL(s));
                while (s.back() == '0') s.pop_back();
                reverse(ALL(s));
                cand.eb(s);
            }
        }

        ll ans = INF;
        for (auto cur : cand) {
            ll cost = 0;
            char c = tochar(startAt);
            rep(i, cur.size()) {
                if (cur[i] != c) {
                    c = cur[i];
                    cost += moveCost;
                }
                cost += pushCost;
            }
            chmin(ans, cost);
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.minCostSetTime(1, 2, 1, 600);
        print(res);
        return 0;
    }
#endif
